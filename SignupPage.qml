import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    // Page Properties
    width: Screen.width
    height: Screen.height
    color: "#1c1c1c"

    // Reference to the main navigation stack
    property StackView stackView: StackView.view

    Connections {
        target: signupWindow

        function onSignupSuccess() {
            console.log("Signup success received.");
            messageDialog.title = "Success";
            messageDialog.messageText = "Account created successfully!";
            messageDialog.visible = true;
        }

        function onSignupFailed(message) {
            console.log("Signup failed: " + message);
            messageDialog.title = "Error";
            messageDialog.messageText = message;
            messageDialog.visible = true;
        }
    }

    Dialog {
        id: messageDialog
        property string messageText: ""
        modal: true
        visible: false

        width: 400
        // Optional: explicitly center dialog on screen
        x: (Screen.width - width) / 2
        y: (Screen.height - height) / 2

        background: Rectangle {
            color: "#80000000"  // semi-transparent black
            radius: 12
        }

        contentItem: Column {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 12

            Text {
                text: messageDialog.title
                font.bold: true
                font.pixelSize: 22
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
            }

            Text {
                text: messageDialog.messageText !== "" ? messageDialog.messageText : " "
                wrapMode: Text.WordWrap
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                width: parent.width
            }
        }

        onAccepted: visible = false
    }


    Connections {
        target: signupWindow
         function onSignupSuccess() {
            console.log("Signup success received.");
            stackView.pop();
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // Left side branding
        Rectangle {
            Layout.preferredWidth: parent.width * 0.42; Layout.fillHeight: true; color: "#1c1c1c";
            Column {
                anchors.centerIn: parent; spacing: 24;

                Rectangle {
                    width: 200; height: 200; radius: 100; color: "transparent"; anchors.horizontalCenter: parent.horizontalCenter;
                    Image { source: "qrc:/images/images/logo.png"; anchors.fill: parent; fillMode: Image.PreserveAspectFit }
                }

                Text { text: "Join the Journey!"; font.pixelSize: 28; font.bold: true; color: "#ffffff"; anchors.horizontalCenter: parent.horizontalCenter }
                Text { text: "Create a new account."; color: "#b0b0b0"; font.pixelSize: 16; anchors.horizontalCenter: parent.horizontalCenter }
            }
        }

        // Right side signup form
        Rectangle {
            Layout.preferredWidth: parent.width * 0.58; Layout.fillHeight: true; color: "#1c1c1c";
            Rectangle {
                width: 420; height: 550; color: "#2a2a2a"; radius: 26; anchors.centerIn: parent;
                border.color: "#3c3c3c"; border.width: 1;

                Column {
                    anchors.centerIn: parent; spacing: 18;

                    Text { text: "Register"; font.pixelSize: 22; color: "#ffffff"; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }

                    // Username field
                    TextField {
                        id: newUserName; placeholderText: "Username"; width: 260; height: 40; font.pixelSize: 16; color: "white";
                        placeholderTextColor: "#a0a0a0"; anchors.horizontalCenter: parent.horizontalCenter; background: Rectangle { color: "#404040"; radius: 8 }
                    }

                    // Password field
                    TextField {
                        id: newPassword; placeholderText: "Password"; echoMode: TextInput.Password; width: 260; height: 40;
                        font.pixelSize: 16; color: "white"; placeholderTextColor: "#a0a0a0"; anchors.horizontalCenter: parent.horizontalCenter;
                        background: Rectangle { color: "#404040"; radius: 8 }
                    }

                    // Confirm password field
                    TextField {
                        id: confirmPassword; placeholderText: "Confirm Password"; echoMode: TextInput.Password; width: 260;
                        height: 40; font.pixelSize: 16; color: "white"; placeholderTextColor: "#a0a0a0";
                        anchors.horizontalCenter: parent.horizontalCenter; background: Rectangle { color: "#404040"; radius: 8 }
                    }

                    // Register button
                    Rectangle {
                        width: 180; height: 46; color: "#d84315"; radius: 14; anchors.horizontalCenter: parent.horizontalCenter;
                        MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: { signupWindow.handleSignup(newUserName.text, newPassword.text, confirmPassword.text) } }
                        Text { text: "Register"; color: "white"; font.bold: true; anchors.centerIn: parent; font.pixelSize: 18 }
                    }

                    // Link to login page
                    Row {
                        anchors.horizontalCenter: parent.horizontalCenter; spacing: 6;
                        Text { text: "Already a member?"; color: "#b0b0b0"; font.pixelSize: 14 }
                        MouseArea {
                            width: loginLink.width; height: loginLink.height; cursorShape: Qt.PointingHandCursor;
                            onClicked: { stackView.push("LoginPage.qml") }
                            Text { id: loginLink; text: "Login"; color: "#ff4d4d"; font.pixelSize: 14; font.bold: true; font.underline: true }
                        }
                    }

                    // Back button
                    Button {
                        text: "Back to Home"; anchors.horizontalCenter: parent.horizontalCenter;
                        background: Rectangle { color: "#4a4a4a"; radius: 8 }
                        contentItem: Text { text: parent.text; color: "white"; font.bold: true; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                        onClicked: { stackView.pop() }
                    }
                }
            }
        }
    }
}
