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

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // Left side branding
        Rectangle {
            Layout.preferredWidth: parent.width * 0.42
            Layout.fillHeight: true
            color: "#1c1c1c"

            Column {
                anchors.centerIn: parent; spacing: 24;

                Rectangle {
                    width: 200; height: 200; radius: 100; color: "transparent"; anchors.horizontalCenter: parent.horizontalCenter;
                    Image { source: "qrc:/images/images/logo.png"; anchors.fill: parent; fillMode: Image.PreserveAspectFit }
                }

                Text { text: "Welcome Back!"; font.pixelSize: 28; font.bold: true; color: "#ffffff"; anchors.horizontalCenter: parent.horizontalCenter }
                Text { text: "Please login to continue."; color: "#b0b0b0"; font.pixelSize: 16; anchors.horizontalCenter: parent.horizontalCenter }
            }
        }

        // Right side login form
        Rectangle {
            Layout.preferredWidth: parent.width * 0.58; Layout.fillHeight: true; color: "#1c1c1c";
            Rectangle {
                width: 400; height: 450; color: "#2a2a2a"; radius: 26; anchors.centerIn: parent;
                border.color: "#3c3c3c"; border.width: 1;

                Column {
                    anchors.centerIn: parent; spacing: 24;

                    Text { text: "Login"; font.pixelSize: 22; color: "#ffffff"; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }

                    // Username field
                    TextField {
                        id: userNameInput; placeholderText: "Username"; width: 260; height: 40; font.pixelSize: 16;
                        color: "white"; placeholderTextColor: "#a0a0a0"; anchors.horizontalCenter: parent.horizontalCenter;
                        background: Rectangle { color: "#404040"; radius: 8 }
                    }

                    // Password field
                    TextField {
                        id: passwordInput; placeholderText: "Password"; echoMode: TextInput.Password; width: 260; height: 40;
                        font.pixelSize: 16; color: "white"; placeholderTextColor: "#a0a0a0"; anchors.horizontalCenter: parent.horizontalCenter;
                        background: Rectangle { color: "#404040"; radius: 8 }
                    }

                    // Login button
                    Rectangle {
                        width: 180; height: 46; color: "#43a047"; radius: 14; anchors.horizontalCenter: parent.horizontalCenter;
                        MouseArea { anchors.fill: parent; cursorShape: Qt.PointingHandCursor; onClicked: { loginWindow.handleLogin(userNameInput.text, passwordInput.text) } }
                        Text { text: "Login"; color: "white"; font.bold: true; anchors.centerIn: parent; font.pixelSize: 18 }
                    }

                    // Link to signup page
                    Row {
                        anchors.horizontalCenter: parent.horizontalCenter; spacing: 6;
                        Text { text: "Don't have an account?"; color: "#b0b0b0"; font.pixelSize: 14 }
                        MouseArea {
                            width: signupLink.width; height: signupLink.height; cursorShape: Qt.PointingHandCursor;
                            onClicked: { stackView.push("SignupPage.qml") }
                            Text { id: signupLink; text: "Sign up"; color: "#2990ff"; font.pixelSize: 14; font.bold: true; font.underline: true }
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
