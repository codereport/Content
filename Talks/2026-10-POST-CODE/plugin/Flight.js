// All positions are screen fractions. A frame-independent timeline lets a
// speaker replay the entrance without depending on refresh rate.
var peekEnd = 1.2
var takeoffStart = 2.1
var flightStart = 4.5
var settleStart = 17.5
var hoverStart = 19.0

function clamp(value, lo, hi) { return Math.max(lo, Math.min(hi, value)) }
function smooth(value) {
  var p = clamp(value, 0, 1)
  return p * p * p * (p * (p * 6 - 15) + 10)
}
function mix(a, b, p) { return a + (b - a) * p }

function pose(t, width, height, size) {
  var cx = width / 2
  var cy = height / 2
  var hiddenY = height + size * 0.34
  var peekY = height + size * 0.03
  var x = cx, y = cy, bank = 0, wingPower = 1
  var phase = "hover"
  if (t < peekEnd) {
    phase = "peek"
    y = mix(hiddenY, peekY, smooth(t / peekEnd))
    wingPower = 0.08
  } else if (t < takeoffStart) {
    phase = "peek"
    y = peekY - Math.pow(Math.sin((t - peekEnd) / (takeoffStart - peekEnd) * Math.PI), 2) * 3
    wingPower = 0.08
  } else if (t < flightStart) {
    phase = "takeoff"
    var p = smooth((t - takeoffStart) / (flightStart - takeoffStart))
    y = mix(peekY, cy, p)
    wingPower = mix(0.08, 1, clamp((t - takeoffStart) / 0.45, 0, 1))
  } else if (t < settleStart) {
    phase = "flight"
    var progress = (t - flightStart) / (settleStart - flightStart)
    var angle = Math.PI * 4 * smooth(progress)
    var radiusX = Math.max(0, Math.min(width * 0.35, cx - size * 0.65))
    var radiusY = Math.max(0, Math.min(height * 0.28, cy - size * 0.65 - 30))
    x = cx + radiusX * Math.sin(angle)
    y = cy + radiusY * Math.sin(2 * angle)
    bank = Math.sin(angle) * 14 * Math.sin(progress * Math.PI)
  } else {
    var hoverGain = smooth((t - settleStart) / (hoverStart - settleStart))
    x = cx + Math.sin((t - settleStart) * 1.3) * 5 * hoverGain
    y = cy + Math.sin((t - settleStart) * 2.7) * 9 * hoverGain
    bank = Math.sin((t - settleStart) * 1.7) * 2 * hoverGain
    phase = t < hoverStart ? "settle" : "hover"
  }
  return {x: x, y: y, bank: bank, wingPower: wingPower, phase: phase,
    titleOpacity: 1 - smooth((t - settleStart) / 1.15)}
}
