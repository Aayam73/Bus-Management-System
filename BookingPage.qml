import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Effects

Rectangle {
    id: root
    width: Screen.width
    height: Screen.height

    // Dark background gradient
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#2c3e50" }
        GradientStop { position: 0.5; color: "#34495e" }
        GradientStop { position: 1.0; color: "#2c3e50" }
    }

    // Floating background elements
    Rectangle {
        anchors.fill: parent
        opacity: 0.04
        Repeater {
            model: 4
            Rectangle {
                width: Math.random() * 80 + 30
                height: width
                radius: width / 2
                color: "#ffffff"
                opacity: 0.4
                x: Math.random() * root.width
                y: Math.random() * root.height
                SequentialAnimation on y {
                    running: true; loops: Animation.Infinite
                    NumberAnimation { to: y - 15; duration: 4000; easing.type: Easing.InOutSine }
                    NumberAnimation { to: y + 15; duration: 4000; easing.type: Easing.InOutSine }
                }
            }
        }
    }

    // Main container
    Rectangle {
        id: mainContainer
        anchors.centerIn: parent
        width: Math.min(root.width * 0.92, 1100)
        height: Math.min(root.height * 0.88, 850)
        radius: 28
        color: "#40ffffff"
        border.color: "#60ffffff"
        border.width: 2
        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowBlur: 2.0
            shadowColor: "#50000000"
            shadowVerticalOffset: 10
            shadowHorizontalOffset: 0
        }
        scale: 0.88
        opacity: 0
        Component.onCompleted: enterAnimation.start()

        // Entry animation
        ParallelAnimation {
            id: enterAnimation
            NumberAnimation { target: mainContainer; property: "scale"; to: 1.0; duration: 550; easing.type: Easing.OutBack }
            NumberAnimation { target: mainContainer; property: "opacity"; to: 1.0; duration: 350 }
        }

        // Content area with fixed layout
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 25
            spacing: 0

            // Header section
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 110
                Layout.topMargin: 0
                Layout.bottomMargin: 20
                radius: 22
                color: "#30ffffff"
                border.color: "#50ffffff"
                border.width: 1

                RowLayout {
                    anchors.centerIn: parent
                    spacing: 18

                    // Title
                    Text {
                        text: "🎫 Booking Confirmation"
                        font.pixelSize: 28
                        font.bold: true
                        color: "#ffffff"
                        layer.enabled: true
                        layer.effect: MultiEffect {
                            shadowEnabled: true
                            shadowBlur: 0.4
                            shadowColor: "#40000000"
                            shadowVerticalOffset: 1
                        }
                    }
                }
            }

            // Details section with ScrollView
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.bottomMargin: 20
                radius: 22
                color: "#30ffffff"
                border.color: "#50ffffff"
                border.width: 1

                ScrollView {
                    anchors.fill: parent
                    anchors.margins: 35
                    contentWidth: availableWidth
                    clip: true

                    ColumnLayout {
                        width: parent.width
                        spacing: 18

                        // Detail rows
                        DetailRow { icon: "🎫"; label: "Route ID"; value: bookingWindow.routeId; Layout.fillWidth: true }
                        DetailRow { icon: "📍"; label: "From"; value: bookingWindow.fromLocation; Layout.fillWidth: true }
                        DetailRow { icon: "📍"; label: "To"; value: bookingWindow.toLocation; Layout.fillWidth: true }
                        DetailRow { icon: "🕒"; label: "Journey Time"; value: bookingWindow.departureTime + " → " + bookingWindow.arrivalTime; Layout.fillWidth: true }
                        DetailRow { icon: "💰"; label: "Ticket Price"; value: "Rs. " + bookingWindow.ticketPrice; Layout.fillWidth: true }
                        DetailRow { icon: "🚌"; label: "Bus Number"; value: bookingWindow.busNo; Layout.fillWidth: true }
                        DetailRow { icon: "👨‍✈️"; label: "Driver"; value: bookingWindow.driverInfo; Layout.fillWidth: true }
                        DetailRow { icon: "📱"; label: "Contact"; value: bookingWindow.contactPhone; Layout.fillWidth: true }
                        DetailRow { icon: "💺"; label: "Seats"; value: bookingWindow.seatNo; Layout.fillWidth: true }

                        // Extra spacing at bottom
                        Item {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 20
                        }
                    }
                }
            }

            // Button section - only Pay Now button
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 80
                color: "transparent"

                RowLayout {
                    anchors.centerIn: parent

                    // Pay button
                    Button {
                        id: payButton
                        text: "💳 Pay Now"
                        implicitWidth: 200
                        implicitHeight: 55
                        background: Rectangle {
                            radius: 28
                            gradient: Gradient {
                                GradientStop { position: 0.0; color: payButton.pressed ? "#27ae60" : "#2ecc71" }
                                GradientStop { position: 1.0; color: payButton.pressed ? "#229954" : "#27ae60" }
                            }
                            border.color: "#58d68d"
                            border.width: 1
                            layer.enabled: true
                            layer.effect: MultiEffect {
                                shadowEnabled: true
                                shadowBlur: payButton.hovered ? 1.8 : 1.0
                                shadowColor: payButton.hovered ? "#2ecc71" : "#27ae60"
                                shadowVerticalOffset: payButton.hovered ? 8 : 5
                                shadowHorizontalOffset: 0
                            }
                        }
                        contentItem: Text {
                            text: payButton.text
                            font.pixelSize: 17
                            font.weight: Font.Bold
                            color: "#ffffff"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        scale: pressed ? 0.94 : (hovered ? 1.06 : 1.0)
                        Behavior on scale { NumberAnimation { duration: 160; easing.type: Easing.OutQuad } }
                        onClicked: paymentAnimation.start()
                    }
                }
            }
        }
    }

    // Detail row component
    component DetailRow: Rectangle {
        property string icon
        property string label
        property string value

        height: 55
        radius: 18
        color: "#20ffffff"
        border.color: "#40ffffff"
        border.width: 1

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: parent.color = "#35ffffff"
            onExited: parent.color = "#20ffffff"
        }

        RowLayout {
            anchors.fill: parent
            anchors.margins: 18
            spacing: 18

            Text {
                text: icon
                font.pixelSize: 20
                Layout.preferredWidth: 35
            }

            Text {
                text: label + ":"
                font.pixelSize: 17
                font.weight: Font.Medium
                color: "#f0f0f0"
                Layout.preferredWidth: 130
                elide: Text.ElideRight
            }

            Text {
                text: value
                font.pixelSize: 17
                font.weight: Font.Bold
                color: "#ffffff"
                Layout.fillWidth: true
                elide: Text.ElideRight
                maximumLineCount: 1
                wrapMode: Text.NoWrap
            }
        }
    }

    // Payment animation
    SequentialAnimation {
        id: paymentAnimation
        NumberAnimation {
            target: payButton
            property: "scale"
            to: 1.12
            duration: 110
        }
        NumberAnimation {
            target: payButton
            property: "scale"
            to: 1.0
            duration: 110
        }
        ScriptAction {
            script: bookingWindow.payNowClicked()
        }
    }
}
