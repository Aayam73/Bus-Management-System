import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: window
    width: 400
    height: 300
    visible: true
    title: "Bus Management System"

    Rectangle {
        anchors.fill: parent
        color: "#f4f6f8"

        Column {
            anchors.centerIn: parent
            spacing: 20

            // Project Logo (Optional, replace source if you add a logo file)
            Image {
                source: "logo.png"  // Add your project logo here
                width: 80;
                height: 80;
                fillMode: Image.PreserveAspectFit
                visible: false // Set to true if you have a logo
            }

            // Title Text
            Text {
                text: "Welcome to Bus Management System"
                font.pixelSize: 20
                color: "#232323"
                horizontalAlignment: Text.AlignHCenter
            }

            // Login and Register Buttons
            Row {
                spacing: 20

                Button {
                    text: "Login"
                    onClicked: {
                        // Add navigation to Login screen
                    }
                }
                Button {
                    text: "Register"
                    onClicked: {
                        // Add navigation to Register screen
                    }
                }
            }

            // Or a single Proceed button
            // Button {
            //     text: "Proceed"
            //     onClicked: {
            //         // Navigate to main menu or dashboard
            //     }
            // }
        }
    }
}
