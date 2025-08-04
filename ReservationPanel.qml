import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Rectangle {
    id: root
    width: Screen.width
    height: Screen.height
    color: "#2d3748"

    property StackView stackView: StackView.view

    ScrollView {
        id: mainScrollView
        anchors.fill: parent
        clip: true

        Column {
            id: mainContent
            width: parent.width
            spacing: 0

            // Header bar
            Rectangle {
                width: parent.width
                height: 120
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#2d3748" }
                    GradientStop { position: 1.0; color: "#4a5568" }
                }

                Row {
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.margins: 25
                    spacing: 20

                    Button {
                        id: backButton
                        text: "← Back"
                        width: 100
                        height: 40
                        font.bold: true
                        font.pixelSize: 14
                        font.family: "Segoe UI"

                        background: Rectangle {
                            color: backButton.pressed ? "#48bb78" : "#68d391"
                            radius: 20
                            border.color: "#68d391"
                            border.width: 2

                            Rectangle {
                                width: parent.width
                                height: parent.height
                                anchors.centerIn: parent
                                anchors.verticalCenterOffset: backButton.pressed ? 0 : -2
                                color: "#00000020"
                                radius: parent.radius
                                z: parent.z - 1
                                visible: !backButton.pressed
                            }
                        }

                        contentItem: Text {
                            text: backButton.text
                            font: backButton.font
                            color: "#ffffff"
                            horizontalAlignment: Qt.AlignHCenter
                            verticalAlignment: Qt.AlignVCenter
                        }

                        onClicked: {
                            if (stackView && stackView.depth > 1) {
                                stackView.pop()
                            }
                        }
                    }

                    Column {
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 5

                        Text {
                            text: "🚌 Your Bookings"
                            font.bold: true
                            font.pixelSize: 28
                            font.family: "Segoe UI"
                            color: "#ffffff"
                        }

                        Text {
                            text: "All your reserved trips at a glance"
                            font.pixelSize: 14
                            font.family: "Segoe UI"
                            color: "#a0aec0"
                        }
                    }
                }
            }

            // Bookings list (detailed styled cards)
            Repeater {
                model: reservationPanel

                Rectangle {
                    width: parent.width - 40
                    height: 160
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: busMouseArea.containsMouse ? "#4a5568" : "#2d3748"
                    radius: 15
                    border.color: "#68d391"
                    border.width: 1
                    Rectangle {
                        width: parent.width
                        height: parent.height
                        anchors.centerIn: parent
                        anchors.verticalCenterOffset: 4
                        color: "#00000025"
                        radius: parent.radius
                        z: parent.z - 1
                    }

                    Row {
                        anchors.fill: parent
                        anchors.margins: 20
                        spacing: 20

                        // Bus Icon + Type (you can expand with bus type if you have it)
                        Column {
                            width: 120
                            anchors.verticalCenter: parent.verticalCenter
                            spacing: 8

                            Rectangle {
                                width: 60
                                height: 60
                                radius: 30
                                color: "#68d391"
                                anchors.horizontalCenter: parent.horizontalCenter

                                Text {
                                    anchors.centerIn: parent
                                    text: "🚍"
                                    font.pixelSize: 30
                                }
                            }

                            Text {
                                // If you have busType role, add here else show bus_no
                                text: model.busNo
                                font.bold: true
                                font.pixelSize: 12
                                color: "#e2f7ec"
                                font.family: "Segoe UI"
                                anchors.horizontalCenter: parent.horizontalCenter
                                elide: Text.ElideRight
                            }
                        }

                        // Main details column
                        Column {
                            width: parent.width - 340
                            anchors.verticalCenter: parent.verticalCenter
                            spacing: 12

                            Text {
                                text: model.fromDistrict + " → " + model.toDistrict
                                font.bold: true
                                font.pixelSize: 18
                                color: "#d1ddf3"
                                font.family: "Segoe UI"
                                elide: Text.ElideRight
                            }

                            Text {
                                text: "Travel Date: " + model.travelDate
                                font.pixelSize: 14
                                color: "#a3b1cf"
                                font.family: "Segoe UI"
                                elide: Text.ElideRight
                            }

                            Row {
                                spacing: 15

                                Row {
                                    spacing: 5
                                    Text {
                                        text: "🕐"
                                        font.pixelSize: 14
                                        color: "#68d391"
                                    }
                                    Text {
                                        text: model.departureTime + " - " + model.arrivalTime
                                        font.pixelSize: 14
                                        color: "#d1ddf3"
                                        font.family: "Segoe UI"
                                    }
                                }

                                Row {
                                    spacing: 5
                                    Text {
                                        text: "💰"
                                        font.pixelSize: 14
                                        color: "#68d391"
                                    }
                                    Text {
                                        text: "Rs. " + model.amount
                                        font.pixelSize: 14
                                        color: "#d1ddf3"
                                        font.family: "Segoe UI"
                                    }
                                }
                            }
                        }

                        // Price & Confirmed label
                        Column {
                            width: 200
                            anchors.verticalCenter: parent.verticalCenter
                            spacing: 15

                            Column {
                                anchors.horizontalCenter: parent.horizontalCenter
                                spacing: 5

                                Text {
                                    text: "Rs. " + model.amount
                                    font.bold: true
                                    font.pixelSize: 22
                                    color: "#68d391"
                                    font.family: "Segoe UI"
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }

                                Text {
                                    text: "per person"
                                    font.pixelSize: 12
                                    color: "#a3b1cf"
                                    font.family: "Segoe UI"
                                }
                            }

                            Rectangle {
                                width: 120
                                height: 30
                                radius: 15
                                color: "#68d391"
                                anchors.horizontalCenter: parent.horizontalCenter

                                Text {
                                    anchors.centerIn: parent
                                    text: "Confirmed"
                                    font.pixelSize: 12
                                    font.bold: true
                                    color: "#ffffff"
                                    font.family: "Segoe UI"
                                }
                            }
                        }
                    }

                    MouseArea {
                        id: busMouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                    }
                }
            }

            Item {
                width: parent.width
                height: 40
            }
        }
    }

    // Footer bar
    Rectangle {
        id: footer
        width: parent.width
        height: 50
        color: "#2d3748"
        border.color: "#68d391"
        border.width: 1
        anchors.bottom: parent.bottom

        Text {
            anchors.centerIn: parent
            text: "© 2025 Hamro Bus Sewa - Your Journey, Our Priority"
            color: "#e2e6f0"
            font.pixelSize: 12
            font.family: "Segoe UI"
        }
    }

    Component.onCompleted: {
        reservationPanel.fetchReservations()
    }
}
