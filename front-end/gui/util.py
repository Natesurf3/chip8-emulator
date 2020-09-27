def inline_replace(oldlist, newlist):
    oldlist.clear()
    oldlist.extend(newlist)

def context_switcher(old):
    return lambda new_type: \
        lambda button: \
            setattr(old, 'next',
                lambda panels: inline_replace(panels, [new_type()] if new_type else [])
            )
