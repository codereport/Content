import QtQuick
import Quickshell
import Quickshell.Io
import Quickshell.Wayland
import "." as Presentation
import "Flight.js" as Flight
import "Location.js" as Location

Item {
  id: root
  property var shell: null
  property bool chooserOpen: false
  property bool starting: false
  property bool exiting: false
  property bool animating: false
  property real elapsed: 0
  property int selectedIndex: 0
  property var config: ({monitor: "DP-4", presentations: []})
  property var deck: ({title: "POST CODE", byline: "Conor Shakory", date: "Oct xx, 2025"})
  property string lastError: ""
  readonly property string presentationFont: regularFont.name || "JetBrainsMono Nerd Font"
  readonly property bool active: Presentation.PresentationState.active
  readonly property string output: active ? Presentation.PresentationState.monitor : String(config.monitor || "DP-4")
  readonly property var targetScreen: {
    var screens = Quickshell.screens
    for (var i = 0; i < screens.length; i++) if (screens[i].name === output) return screens[i]
    return null
  }
  readonly property string sessionHelper: Quickshell.env("HOME") + "/.local/bin/post-code-session"
  readonly property string configPath: Location.projectConfigPath || Qt.resolvedUrl("../presentations.json").toString().replace(/^file:\/\//, "")

  function openChooser() {
    if (starting || exiting) return
    lastError = ""
    chooserOpen = !chooserOpen
    selectedIndex = 0
    Qt.callLater(function() { keys.forceActiveFocus() })
  }
  function begin() {
    if (starting || exiting || !targetScreen || config.presentations.length === 0) return
    lastError = ""
    deck = config.presentations[selectedIndex]
    if (active) { chooserOpen = false; replayTitle(); return }
    starting = true
    session.command = [sessionHelper, "enter", output]
    session.running = true
  }
  function end() {
    if (starting || exiting) return
    chooserOpen = false
    if (!active) return
    exiting = true
    animating = false
    elapsed = 0
    Presentation.PresentationState.active = false
    session.command = [sessionHelper, "exit"]
    session.running = true
  }
  function advance() {
    if (!active || chooserOpen || starting || exiting) return
    elapsed = 0
    animating = true
    frames.reset()
  }
  function replayTitle() { animating = false; elapsed = 0 }

  FontLoader { id: regularFont; source: "assets/fonts/JetBrainsMono-Regular.ttf" }
  FontLoader { id: titleFont; source: "assets/fonts/JetBrainsMono-ExtraBold.ttf" }
  FontLoader { id: displayTitleFont; source: "assets/fonts/RussoOne-Regular.ttf" }

  FileView {
    id: configFile
    path: root.configPath
    watchChanges: true
    onFileChanged: reload()
    onLoaded: {
      try {
        var next = JSON.parse(text())
        if (!Array.isArray(next.presentations)) throw new Error("presentations must be an array")
        root.config = next
      } catch (error) { root.lastError = "Cannot read presentation list: " + error }
    }
  }

  Process {
    id: session
    stderr: StdioCollector { onStreamFinished: if (text.trim()) root.lastError = text.trim() }
    onExited: function(code) {
      if (root.starting) {
        root.starting = false
        if (code === 0) {
          Presentation.PresentationState.monitor = root.output
          Presentation.PresentationState.active = true
          root.chooserOpen = false
          root.replayTitle()
          Qt.callLater(function() { keys.forceActiveFocus() })
        } else if (!root.lastError) root.lastError = "Could not start presentation."
      } else root.exiting = false
    }
  }

  FrameAnimation {
    id: frames
    running: root.active && root.animating
    onTriggered: root.elapsed += frameTime
  }

  IpcHandler {
    target: "cph.presentations"
    function toggle(): void { root.openChooser() }
    function start(): void { root.begin() }
    function next(): void { root.advance() }
    function title(): void { root.replayTitle() }
    function stop(): void { root.end() }
    function status(): string {
      return JSON.stringify({active: root.active, chooser: root.chooserOpen, starting: root.starting,
        monitor: root.output, title: root.deck.title, presentations: root.config.presentations.length, time: root.elapsed,
        phase: root.animating ? Flight.pose(root.elapsed, 2560, 1440, 400).phase : "title",
        error: root.lastError})
    }
  }

  PanelWindow {
    id: surface
    screen: root.targetScreen
    visible: root.targetScreen !== null && (root.active || root.chooserOpen)
    color: "transparent"
    exclusionMode: ExclusionMode.Ignore
    anchors { top: true; left: true; right: true; bottom: true }
    WlrLayershell.namespace: "post-code-presentation"
    WlrLayershell.layer: WlrLayer.Overlay
    WlrLayershell.keyboardFocus: visible ? WlrKeyboardFocus.Exclusive : WlrKeyboardFocus.None

    IdleInhibitor { window: surface; enabled: root.active }

    Item {
      id: keys
      anchors.fill: parent
      focus: true
      clip: true
      Keys.onPressed: function(event) {
        if (event.isAutoRepeat) { event.accepted = true; return }
        if (event.key === Qt.Key_Escape) {
          if (root.chooserOpen) root.chooserOpen = false
          else root.end()
        } else if (root.chooserOpen) {
          if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter || event.key === Qt.Key_Space) root.begin()
          else if (event.key === Qt.Key_Down) root.selectedIndex = Math.min(root.config.presentations.length - 1, root.selectedIndex + 1)
          else if (event.key === Qt.Key_Up) root.selectedIndex = Math.max(0, root.selectedIndex - 1)
        } else if (event.key === Qt.Key_Space || event.key === Qt.Key_Right || event.key === Qt.Key_Return || event.key === Qt.Key_PageDown) root.advance()
        else if (event.key === Qt.Key_Left || event.key === Qt.Key_Backspace || event.key === Qt.Key_Home) root.replayTitle()
        else { event.accepted = false; return }
        event.accepted = true
      }

      Item {
        id: stage
        anchors.fill: parent
        visible: root.active
        readonly property real birdSize: Math.min(width * 0.19, height * 0.34)
        readonly property var pose: Flight.pose(root.elapsed, width, height, birdSize)

        Column {
          anchors.horizontalCenter: parent.horizontalCenter
          y: parent.height * 0.36
          spacing: Math.round(parent.height * 0.018)
          opacity: root.animating ? stage.pose.titleOpacity : 1
          Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.deck.title
            color: "#ffffff"
            font.family: displayTitleFont.name || root.presentationFont
            font.pixelSize: Math.round(stage.width * 0.066)
            font.weight: Font.Normal
            font.letterSpacing: stage.width * 0.004
          }
          Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.deck.byline
            color: "#ffffff"
            font.family: root.presentationFont
            font.pixelSize: Math.round(stage.width * 0.022)
            font.weight: Font.Medium
            style: Text.Raised
            styleColor: "#442342"
          }
          Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.deck.date
            color: "#f5e9f5"
            font.family: root.presentationFont
            font.pixelSize: Math.round(stage.width * 0.014)
            topPadding: stage.height * 0.014
            style: Text.Raised
            styleColor: "#442342"
          }
        }

        Parrot {
          visible: root.animating
          width: stage.birdSize
          height: width
          x: stage.pose.x - width / 2
          y: stage.pose.y - height / 2
          rotation: stage.pose.bank
          time: root.elapsed
          wingPower: stage.pose.wingPower
        }
        MouseArea {
          anchors.fill: parent
          acceptedButtons: Qt.LeftButton | Qt.RightButton
          enabled: !root.chooserOpen
          onClicked: function(mouse) { if (mouse.button === Qt.RightButton) root.replayTitle(); else root.advance() }
        }
      }

      Rectangle {
        id: dialog
        visible: root.chooserOpen
        anchors.centerIn: parent
        width: Math.min(540, parent.width * 0.8)
        height: contents.implicitHeight + 56
        radius: 0
        color: "#b81b152b"
        border.color: "#7b6593"
        border.width: 1

        Column {
          id: contents
          anchors { left: parent.left; right: parent.right; top: parent.top; margins: 28 }
          spacing: 16
          Text {
            text: "PRESENTATIONS"
            color: "#c6b6dd"
            font.family: root.presentationFont
            font.pixelSize: 13
            font.weight: Font.Bold
            font.letterSpacing: 2
          }
          Repeater {
            model: root.config.presentations
            Rectangle {
              required property var modelData
              required property int index
              width: contents.width
              height: 90
              radius: 0
              color: root.selectedIndex === index ? "#70423252" : "transparent"
              border.color: root.selectedIndex === index ? "#a893c7" : "#483851"
              Column {
                anchors { left: parent.left; verticalCenter: parent.verticalCenter; leftMargin: 18 }
                spacing: 7
                Text { text: modelData.title; color: "#ffffff"; font.family: root.presentationFont; font.pixelSize: 26; font.weight: Font.Bold; font.letterSpacing: 1 }
                Text { text: modelData.byline + "  ·  " + modelData.date; color: "#c6b6dd"; font.family: root.presentationFont; font.pixelSize: 14 }
              }
              MouseArea { anchors.fill: parent; onClicked: { root.selectedIndex = index; root.begin() } }
            }
          }
          Text {
            width: parent.width
            text: root.lastError || (root.starting ? "Starting…" : "Enter to present   ·   Esc to cancel")
            color: root.lastError ? "#ffaaaa" : "#b4a4c8"
            font.family: root.presentationFont
            font.pixelSize: 13
            wrapMode: Text.Wrap
          }
          Text {
            visible: root.active
            text: "End presentation"
            color: "#eee2ff"
            font.family: root.presentationFont
            font.pixelSize: 14
            MouseArea { anchors.fill: parent; onClicked: root.end() }
          }
        }
      }
    }
  }

  onTargetScreenChanged: if (!targetScreen && active) end()
  Component.onDestruction: {
    if (root.active) {
      Presentation.PresentationState.active = false
      Quickshell.execDetached([root.sessionHelper, "exit"])
    }
  }
}
