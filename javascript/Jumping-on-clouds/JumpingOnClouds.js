function canJumpTwo(arr, index) {
  var n = arr.length

	if(index + 2 > n - 1) { return false }

  if(arr[index + 2] === 1) { return false }

	return true
}

function jumpingOnClouds(c) {
  var jumps = 0
  var n = c.length
  var index = 0

  while(index < n - 1) {
		if(!canJumpTwo(c, index)) {
		  jumps++
      index += 1
    } else {
			jumps++
			index += 2
    }
	}

  return jumps
}

function toInt(value) {
	return parseInt(value)
}

var actual = jumpingOnClouds('00'.split('').map(toInt))
console.log({expected: 1, actual})

actual = jumpingOnClouds('0010010'.split('').map(toInt))
console.log({expected: 4, actual})

actual = jumpingOnClouds('000010'.split('').map(toInt))
console.log({expected: 3, actual})

actual = jumpingOnClouds('0100010'.split('').map(toInt))
console.log({expected: 3, actual})
