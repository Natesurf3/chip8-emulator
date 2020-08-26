const program = `a2b4 23e6 22b6 7001 d011 3025 1206 71ff
d011 601a d011 6025 3100 120e c470 4470
121c c303 601e 6103 225c f515 d014 3f01
123c d014 71ff d014 2340 121c e7a1 2272
e8a1 2284 e9a1 2296 e29e 1250 6600 f615
f607 3600 123c d014 7101 122a a2c4 f41e
6600 4301 6604 4302 6608 4303 660c f61e
00ee d014 70ff 2334 3f01 00ee d014 7001
2334 00ee d014 7001 2334 3f01 00ee d014
70ff 2334 00ee d014 7301 4304 6300 225c
2334 3f01 00ee d014 73ff 43ff 6303 225c
2334 00ee 8000 6705 6806 6904 611f 6510
6207 00ee 40e0 0000 40c0 4000 00e0 4000
4060 4000 4040 6000 20e0 0000 c040 4000
00e0 8000 4040 c000 00e0 2000 6040 4000
80e0 0000 40c0 8000 c060 0000 40c0 8000
c060 0000 80c0 4000 0060 c000 80c0 4000
0060 c000 c0c0 0000 c0c0 0000 c0c0 0000
c0c0 0000 4040 4040 00f0 0000 4040 4040
00f0 0000 d014 6635 76ff 3600 1338 00ee
a2b4 8c10 3c1e 7c01 3c1e 7c01 3c1e 7c01
235e 4b0a 2372 91c0 00ee 7101 1350 601b
6b00 d011 3f00 7b01 d011 7001 3025 1362
00ee 601b d011 7001 3025 1374 8e10 8de0
7eff 601b 6b00 d0e1 3f00 1390 d0e1 1394
d0d1 7b01 7001 3025 1386 4b00 13a6 7dff
7eff 3d01 1382 23c0 3f01 23c0 7a01 23c0
80a0 6d07 80d2 4004 75fe 4502 6504 00ee
a700 f255 a804 fa33 f265 f029 6d32 6e00
dde5 7d05 f129 dde5 7d05 f229 dde5 a700
f265 a2b4 00ee 6a00 6019 00ee 3723`

const SCREEN_LENGTH = 32
const SCREEN_HEIGHT = 64

class Display {
	constructor() {
		this.pixels = new Array(SCREEN_LENGTH*SCREEN_HEIGHT).fill(0);
	}

	clear() {
		this.pixels = new Array(SCREEN_LENGTH*SCREEN_HEIGHT).fill(0);
	}

	add_sprite_Row(x, y, byte) {
		var start_loc_in_buffer = y * 32 + x
		const wrap_at = 32 - x

		for (var i = 0; i++; i < 8) {
			const bit_loc = start_loc_in_buffer + i % SCREEN_LENGTH
			const pixel_in_sprite = (byte & (1 << (8 - i)))
			const next_pixel = this.pixels[bit_loc] ^ pixel_in_sprite

			this.pixels[bit_loc] = next_pixel
		}
	}
	add_sprite(x, y, sprite) {
		for (var i = 0; i++; i <= sprite.length) {
			this.add_sprite_row(x, y, sprite[i])
		}
	}
}

class Stack {
	constructor() {
		this.memory = new Array(16).fill(0)
		this.sp = 0
	}

	push(val) {
		if (this.sp === 15) {throw new Error("Stack pointer incremented past limit.")}
		this.sp++
		this.memory[this.sp] = val
	}

	pop() {
		const out = this.memory[this.sp]
		sp--
		return out
	}
}
class VRegister {
	constructor() {
		this.value = 0
	}

	add(val) {
		let next = (this.value + val) % 256
		this.value = next
	}

	get() {
		return this.value
	}

	set(val) {
		this.value = val
	}

	static zero() {
		return new VRegister()
	}
}

class VRegisters {
	constructor() {
		this.registers = Array(16).fill(new VRegister)
	}

	get(idx) {
		return this.registers[idx].get()
	}

	set(idx, value) {
		this.registers[idx].set(value)
	}

	add(idx, val) {
		this.registers[idx].add(val)
	}
}

class CPU {
	constructor(display) {
		this.display = new Display()
		this.stack = new Stack()
		this.pc = 0x200
		this.i_register = 0
		this.v_registers = new VRegisters()
	}

	load() {
		this.rom = program
			.split(' ')
			.map(word => {
				console.log(word)
				return [word.slice(0,2), word.slice(2,4)]
			})
			.map(byte => {console.log(byte); return byte})
			.flat()
	}

	print() {
		console.log(`ROM: ${this.rom.length}: ${this.rom}`)
	}

	setIRegister(val) {
		this.i_reg = val
	}

	fetch() {
		//code is supposed to be loaded into 0x0200
		const loc = this.pc - 0x200
		return (parseInt(this.rom[loc], 16) << 8) + (parseInt(this.rom[loc+1, 16]));
	}

	get_sprite(start_location, number_of_bytes) {
		return this.rom.slice(start_location, start_location + number_of_bytes)
	}

	decode(instruction) {
		const family = (instruction & 0xF000) >> 12
		const rest = (instruction & 0x0FFF)
		const low_nibble_of_higher_byte = (instruction & 0x0F00) >> 8
		const low_byte = (instruction & 0x00FF)

		let v_reg_idx = null // Seems bad, but I can't define it multiple times in the switch.

		switch (family) {
			case 0: // display clear/
				if (rest != 0x0EE) {
					this.display.clear()
				}
				else {
					this.pc = this.stack.pop()
				}
				break;
			case 2:
				console.log(`${instruction.toString(16)}: Setting PC=${this.pc} to ${rest.toString(16)}.`)
				this.stack.push(this.pc)
				this.pc = rest
				break;
			case 3:
				console.log(`${instruction.toString(16)}: ${this.v_registers.get(low_nibble_of_higher_byte)} == ${low_byte}? -> pc += 2`)
				v_reg_idx = low_nibble_of_higher_byte
				const value_to_compare = low_byte

				if (this.v_registers.get(v_reg_idx) == value_to_compare) this.pc += 2

				break;
			case 0x6:
				console.log(`${instruction.toString(16)}: Setting register ${low_nibble_of_higher_byte} to ${low_byte}.`)
				v_reg_idx = low_nibble_of_higher_byte
				const value_to_set = low_byte

				this.v_registers.set(v_reg_idx, value_to_set)
				break;
			case 0x7:
				console.log(`${instruction.toString(16)}: Adding value ${low_byte} to register ${low_nibble_of_higher_byte}`)
				v_reg_idx = low_nibble_of_higher_byte
				const value_to_add = low_byte

				this.v_registers.add(v_reg_idx, value_to_add)
				break;
			case 0xa:
				console.log(`${instruction.toString(16)}: Setting i register to ${rest}`)
				this.setIRegister(rest)
				break;
			case 0xd:
				const vx_idx = low_nibble_of_higher_byte
				const vy_idx = (low_byte & 0xF0) >> 4
				const start_location = this.i_reg
				const sprite_height = (low_byte & 0x0F) // number of bytes to retrieve
				const next_x = this.v_registers.get(vx_idx)
				const next_y = this.v_registers.get(vy_idx)
				console.log(`Drawing sprite of height ${sprite_height} from loc: ${start_location} to (${next_x}, ${next_y}).`)

				const sprite = this.get_sprite(start_location, sprite_height)
				this.display.add_sprite(next_x, next_y, sprite)

				break;
			default:
				throw new Error(`Opcode "${((instruction & 0xF000) >> 12).toString(16)}" not implemented. [${instruction.toString(16)}]`)
		}
	}

	tick() {
		const currentInstruction = this.fetch()
		this.decode(currentInstruction)

		this.pc += 2;
	}
}


const cpu = new CPU()


cpu.load();
cpu.print();

for (var i = 0; i <= 10; i++) {
	cpu.tick()
}
