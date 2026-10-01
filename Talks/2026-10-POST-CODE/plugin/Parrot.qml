import QtQuick

Item {
  id: bird
  property real time: 0
  property real wingPower: 1
  readonly property real stroke: Math.sin(time * Math.PI * 2 * 3.2)
  readonly property real wingAngle: wingPower * (12 + stroke * 44)

  Image {
    anchors.fill: parent
    source: "assets/left-wing.svg"
    sourceSize: Qt.size(1000, 1000)
    smooth: true
    transform: [
      Scale { origin.x: bird.width * 0.29; origin.y: bird.height * 0.44; yScale: 1 - bird.wingPower * (1 - bird.stroke) * 0.21 },
      Rotation { origin.x: bird.width * 0.29; origin.y: bird.height * 0.44; angle: -bird.wingAngle }
    ]
  }
  Image {
    anchors.fill: parent
    source: "assets/right-wing.svg"
    sourceSize: Qt.size(1000, 1000)
    smooth: true
    transform: [
      Scale { origin.x: bird.width * 0.71; origin.y: bird.height * 0.44; yScale: 1 - bird.wingPower * (1 - bird.stroke) * 0.21 },
      Rotation { origin.x: bird.width * 0.71; origin.y: bird.height * 0.44; angle: bird.wingAngle }
    ]
  }
  Image {
    anchors.fill: parent
    source: "assets/body.svg"
    sourceSize: Qt.size(1000, 1000)
    smooth: true
    rotation: Math.sin(bird.time * Math.PI * 2 * 3.2 + 0.35) * bird.wingPower * 1.3
  }
}
