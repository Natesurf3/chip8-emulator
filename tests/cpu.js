const program = `6e05 6500 6b06 6a00 a30c dab1 7a04 3a40
1208 7b02 3b12 1206 6c20 6d1f a310 dcd1
22f6 6000 6100 a312 d011 7008 a30e d011
6040 f015 f007 3000 1234 c60f 671e 6801
69ff a30e d671 a310 dcd1 6004 e0a1 7cfe
6006 e0a1 7c02 603f 8c02 dcd1 a30e d671
8684 8794 603f 8602 611f 8712 471f 12ac
4600 6801 463f 68ff 4700 6901 d671 3f01
12aa 471f 12aa 6005 8075 3f00 12aa 6001
f018 8060 61fc 8012 a30c d071 60fe 8903
22f6 7501 22f6 4560 12de 1246 69ff 8060
80c5 3f01 12ca 6102 8015 3f01 12e0 8015
3f01 12ee 8015 3f01 12e8 6020 f018 a30e
7eff 80e0 8004 6100 d011 3e00 1230 12de
78ff 48fe 68ff 12ee 7801 4802 6801 6004
f018 69ff 1270 a314 f533 f265 f129 6337
6400 d345 7305 f229 d345 00ee e000 8000
fc00 aa00 0000 0000`

const SCREEN_LENGTH = 32
const SCREEN_HEIGHT = 64

const PC_START = 0x200

class Logger { // yeah.... I SHOULD just use a good one.
	constructor(levels = ["debug", "message", "warning", "error"], preamble = () => {}) { // Preamble is a function to make it dynamic
		this.levels = levels
		this.messageLog = []
		this.min_level_idx = 0
		this.hushed = false
		this.preamble = preamble
	}

	log(message, level="message") {
		var level_idx = this.levels.indexOf(level)

		if (level_idx === -1) console.error("Bad level given to logger.")

		if ((level_idx >= this.min_level_idx) & !this.hushed) {
			console.log(`${this.preamble()}${message}`)
		}
	}

	debug(message) {
		this.log(message, "debug")
	}
	hush() {
		this.hushed = true
	}

	unhush() {
		this.hushed = false
	}

	setPreambleCallback(cb) {
		this.preamble = cb
	}
}

class Display {
	constructor() {
		this.pixels = new Array(SCREEN_LENGTH*SCREEN_HEIGHT).fill(0);
	}

	clear() {
		this.pixels = new Array(SCREEN_LENGTH*SCREEN_HEIGHT).fill(0);
	}

	add_sprite_Row(x, y, byte) {
		var start_loc_in_buffer = y * 32 + x
		const start_row_loc_in_buffer = y*32

		const wrap_at = 32 - x

		for (var i = 0; i++; i < 8) {
			const bit_loc = start_row_loc_in_buffer + ((x+i) % SCREEN_LENGTH) // modulo for wrap-around effect
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

const logger = new Logger()

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
		this.pc = PC_START
		this.i_register = 0
		this.v_registers = new VRegisters()
		this.logger = new Logger()
		this.rom = []

		console.log(typeof(logger))
		logger.setPreambleCallback(() => {
			return `[PC=0x${this.pc.toString(16)};Opcode=${this.fetch().toString(16)}] `
		})
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
		logger.log(`ROM: ${this.rom.length}: ${this.rom}`)
	}

	setIRegister(val) {
		this.i_reg = val
	}

	fetch() {
		//code is supposed to be loaded into 0x0200
		const loc = this.pc - PC_START
		return (parseInt(this.rom[loc], 16) << 8) + (parseInt(this.rom[loc+1], 16));
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
			case 0x0: // display clear/
				if (rest != 0x0EE) {
					this.display.clear()
				}
				else {
					this.pc = this.stack.pop()
				}
				break;
			case 0x1:
				logger.debug(`Jumping to ${rest.toString(16)}`)
				this.pc = rest
				break
			case 0x2:
				logger.debug(`Setting PC=${this.pc.toString(16)} to ${rest.toString(16)}.`)
				this.stack.push(this.pc)
				this.pc = rest
				break;
			case 0x3:
				logger.debug(`${this.v_registers.get(low_nibble_of_higher_byte)} == ${low_byte}? -> pc += 2`)
				v_reg_idx = low_nibble_of_higher_byte
				const value_to_compare = low_byte

				if (this.v_registers.get(v_reg_idx) == value_to_compare) this.pc += 2

				break;
			case 0x4:
				v_reg_idx = low_nibble_of_higher_byte
				let value_to_check = low_byte

				logger.debug(`Checking if ${this.v_registers.get(v_reg_idx)} != ${value_to_check}`)
				if (this.v_registers.get(v_reg_idx) != v_reg_idx) this.pc +=2
				break;
			case 0x6:
				logger.debug(`Setting register ${low_nibble_of_higher_byte} to ${low_byte}.`)
				v_reg_idx = low_nibble_of_higher_byte
				const value_to_set = low_byte

				this.v_registers.set(v_reg_idx, value_to_set)
				break;
			case 0x7:
				logger.debug(`Adding value ${low_byte} to register ${low_nibble_of_higher_byte}`)
				v_reg_idx = low_nibble_of_higher_byte
				const value_to_add = low_byte

				this.v_registers.add(v_reg_idx, value_to_add)
				break;
			case 0xa:
				logger.debug(`Setting i register to ${rest.toString(16)}`)
				this.setIRegister(rest)
				break;
			case 0xd:
				const vx_idx = low_nibble_of_higher_byte
				const vy_idx = (low_byte & 0xF0) >> 4
				const start_location = this.i_reg
				const sprite_height = (low_byte & 0x0F) // number of bytes to retrieve
				const next_x = this.v_registers.get(vx_idx)
				const next_y = this.v_registers.get(vy_idx)
				logger.debug(`Drawing sprite of height ${sprite_height} from loc: ${start_location.toString(16)} to (${next_x}, ${next_y}).`)

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

for (var i = 0; i <= 100; i++) {
	cpu.tick()
}
