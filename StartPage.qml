import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    // Window Properties
    id: mainWindow
    visible: true
    title: "Hamro Bus Sewa"
    width: 1100
    height: 670
    visibility: "Maximized"

    // Set main window background to black
    background: Rectangle {
        color: "#000000"
    }

    // Navigation handler for switching pages
    StackView {
        id: pageStack
        anchors.fill: parent
        initialItem: startPage
    }

    // Component for the start page content
    Component {
        id: startPage

        Rectangle {
            width: parent.width
            height: parent.height
            color: "transparent"

            RowLayout {
                anchors.fill: parent
                spacing: 0

                // Left side branding panel
                Rectangle {
                    Layout.preferredWidth: parent.width * 0.42
                    Layout.fillHeight: true
                    color: "#1c1c1c"

                    Column {
                        anchors.centerIn: parent
                        spacing: 32

                        // Logo display
                        Rectangle {
                            width: 200; height: 200; radius: 100; color: "transparent";
                            anchors.horizontalCenter: parent.horizontalCenter
                            Image {
                                source: "qrc:/images/images/logo.png"; anchors.fill: parent;
                                fillMode: Image.PreserveAspectFit
                            }
                        }

                        // Brand name in Nepali
                        Text {
                            text: "हाम्रो बस सेवा"; font.pixelSize: 38; color: "#ffffff";
                            font.family: "Nirmala UI"; font.bold: true;
                            horizontalAlignment: Text.AlignHCenter; anchors.horizontalCenter: parent.horizontalCenter
                        }

                        // Subtitle
                        Text {
                            text: "Smart. Simple. Secure."; color: "#b0b0b0";
                            font.pixelSize: 18; anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                }

                // Right side content panel
                Rectangle {
                    Layout.preferredWidth: parent.width * 0.58
                    Layout.fillHeight: true
                    color: "#1c1c1c"

                    Rectangle {
                        width: Math.min(parent.width * 0.65, 445); height: Math.min(parent.height * 0.60, 405);
                        color: "#2a2a2a"; radius: 32;
                        anchors.centerIn: parent;
                        border.color: "#3c3c3c"; border.width: 1;

                        Column {
                            anchors.centerIn: parent; spacing: 30;

                            Text {
                                text: "Let's get you started"; font.pixelSize: 22;
                                color: "#ffffff"; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter
                            }

                            Text {
                                text: "Please login or create a new account."; font.pixelSize: 15;
                                color: "#b0b0b0"; anchors.horizontalCenter: parent.horizontalCenter
                            }

                            // Login and Register buttons
                            Row {
                                spacing: 38; anchors.horizontalCenter: parent.horizontalCenter;

                                Rectangle {
                                    width: 140; height: 46; color: "#43a047"; radius: 14;
                                    border.color: "#a5d6a7"; border.width: 2;
                                    MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: {  pageStack.push("qrc:/Qml/LoginPage.qml") } }
                                    Text { text: "Login"; color: "white"; font.pixelSize: 18; font.bold: true; anchors.centerIn: parent }
                                }

                                Rectangle {
                                    width: 140; height: 46; color: "#d84315"; radius: 14;
                                    border.color: "#ffab91"; border.width: 2;
                                    MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: { pageStack.push("qrc:/Qml/SignupPage.qml") } }
                                    Text { text: "Register"; color: "white"; font.pixelSize: 18; font.bold: true; anchors.centerIn: parent }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
