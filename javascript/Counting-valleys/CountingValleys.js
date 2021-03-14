function isUp(value) {
	if(value === 'U') { return true }

	return false
}

function isNewVally(plevel, level) {
  if(level === -1 && plevel === 0) { return true }

	return false
}

function countingValleys(_steps, path) {
  var level = 0
  var plevel = 0
  var valleys = 0

	path = path.split('')

  path.forEach((current) => {
    plevel = level

    if(isUp(current)) {
		  level++

			return
    } 

	  level--
		
		if(!isNewVally(plevel, level)) { return }

		valleys++
  })

  return valleys
}

var valleys1 = countingValleys(0, 'DUUUDUUDDDDDUUUD')
console.log({expected: 2, valleys1})

valleys1 = countingValleys(0, 'DUUUDUUDDDDDUUUDDU')
console.log({expected: 3, valleys1})

valleys1 = countingValleys(0, 'DDUUUUDD')
console.log({expected: 1, valleys1})

valleys1 = countingValleys(0, '')
console.log({expected: 0, valleys1})

valleys1 = countingValleys(0, 'UD')
console.log({expected: 0, valleys1})

valleys1 = countingValleys(0, 'DU')
console.log({expected: 1, valleys1})

valleys1 = countingValleys(0, 'UUDD')
console.log({expected: 0, valleys1})
