import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Rectangle {
    id: root
    width: Screen.width
    height: Screen.height
    color: "#2d3748"  // Dark background matching your login screen

    property bool isEditMode: false
    property string username: ""
    property StackView stackView: StackView.view

    Component.onCompleted: {
        console.log("AccountPage loaded with username:", username)
        accountWindow.username = username
    }

    // Smooth scroll behavior
    ScrollView {
        id: mainScrollView
        anchors.fill: parent
        clip: true
        contentHeight: mainContent.height + 100

        Column {
            id: mainContent
            width: parent.width
            spacing: 0

            // Header Section - Dark theme
            Rectangle {
                width: parent.width
                height: 150
                color: "#2d3748"  // Matching dark background

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
                            color: backButton.pressed ? "#48bb78" : "#68d391"  // Green color matching your theme
                            radius: 20
                            border.color: "#68d391"
                            border.width: 2
                        }

                        contentItem: Text {
                            text: backButton.text
                            font: backButton.font
                            color: "#ffffff"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        onClicked: {
                            if (stackView && stackView.depth > 1) {
                                stackView.pop()
                            }
                        }
                    }

                    Text {
                        text: "My Account"
                        font.bold: true
                        font.pixelSize: 32
                        font.family: "Segoe UI"
                        color: "#ffffff"  // White text on dark background
                        anchors.verticalCenter: backButton.verticalCenter
                    }
                }
            }

            // Main Content Area
            Item {
                width: parent.width
                height: childrenRect.height

                Row {
                    id: contentRow
                    width: parent.width - 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    spacing: 40

                    // Left Column - User Profile
                    Rectangle {
                        id: userProfileCard
                        width: (parent.width - parent.spacing) / 2
                        height: 700
                        color: "#4a5568"  // Dark card background matching your design
                        radius: 20
                        border.color: "#68d391"  // Green border
                        border.width: 1

                        // Shadow effect
                        Rectangle {
                            width: parent.width
                            height: parent.height
                            anchors.centerIn: parent
                            anchors.verticalCenterOffset: 4
                            color: "#00000025"
                            radius: parent.radius
                            z: parent.z - 1
                        }

                        Column {
                            anchors.fill: parent
                            anchors.margins: 30
                            spacing: 25

                            Text {
                                text: "User Details"
                                font.bold: true
                                font.pixelSize: 24
                                color: "#ffffff"  // White text
                                font.family: "Segoe UI"
                            }

                            // Profile Picture Section
                            Item {
                                width: parent.width
                                height: 180

                                Rectangle {
                                    id: profilePicture
                                    width: 120
                                    height: 120
                                    radius: 60
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    color: "#68d391"  // Green profile background

                                    Image {
                                    id: profileImage
                                    anchors.fill: parent
                                    source: accountWindow.profilePic // This is now bound to the C++ property
                                    fillMode: Image.PreserveAspectCrop
                                    clip: true
                                    visible: accountWindow.profilePic !== ""
                                    }

                                    Text {
                                        anchors.centerIn: parent
                                        text:accountWindow.username.charAt(0).toUpperCase()
                                        font.bold: true
                                        font.pixelSize: 48
                                        color: "#ffffff"
                                        font.family: "Segoe UI"
                                        visible: accountWindow.profilePic === ""
                                    }

                                    MouseArea {
                                        anchors.fill: parent
                                        cursorShape: Qt.PointingHandCursor
                                        onClicked: {
                                            accountWindow.openFileSelectionDialog()
                                            console.log("Change profile picture")
                                        }
                                    }
                                }

                                Button {
                                    text: "Change Photo"
                                    width: 120
                                    height: 35
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    anchors.bottom: parent.bottom
                                    font.pixelSize: 12
                                    font.family: "Segoe UI"

                                    background: Rectangle {
                                        color: "#68d391"  // Green button
                                        radius: 17
                                        border.color: "#48bb78"
                                        border.width: 1
                                    }

                                    contentItem: Text {
                                        text: parent.text
                                        font: parent.font
                                        color: "#ffffff"
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                    }

                                    onClicked: {
                                        accountWindow.openFileSelectionDialog()
                                    }
                                }
                            }

                            // User Information Fields
                            Column {
                                width: parent.width
                                spacing: 20

                                // Name Field - ALWAYS DISABLED
                                Column {
                                    width: parent.width
                                    spacing: 8

                                    Text {
                                        text: "Username"
                                        font.bold: true
                                        font.pixelSize: 14
                                        color: "#e2e8f0"  // Light gray text
                                        font.family: "Segoe UI"
                                    }

                                    Rectangle {
                                        width: parent.width
                                        height: 45
                                        color: "#2d3748"  // Darker background for non-editable
                                        border.color: "#68d391"
                                        border.width: 2
                                        radius: 10

                                        Text {
                                            anchors.left: parent.left
                                            anchors.leftMargin: 15
                                            anchors.verticalCenter: parent.verticalCenter
                                            text: accountWindow.username
                                            font.pixelSize: 15
                                            font.family: "Segoe UI"
                                            color: "#a0aec0"
                                        }

                                        Connections {
                                            target: accountWindow
                                            onUsernameChanged: {
                                                console.log("QML Received - Username:", accountWindow.username)
                                            }
                                        }

                                        // Lock icon to indicate non-editable
                                        Text {
                                            anchors.right: parent.right
                                            anchors.rightMargin: 15
                                            anchors.verticalCenter: parent.verticalCenter
                                            text: "🔒"
                                            font.pixelSize: 14
                                            color: "#68d391"
                                        }
                                    }
                                }

                                // Email Field
                                Column {
                                    width: parent.width
                                    spacing: 8

                                    Text {
                                        text: "Email Address"
                                        font.bold: true
                                        font.pixelSize: 14
                                        color: "#e2e8f0"
                                        font.family: "Segoe UI"
                                    }

                                    TextField {
                                        id: emailField
                                        width: parent.width
                                        height: 45
                                        text: accountWindow.email
                                        enabled: isEditMode
                                        font.pixelSize: 15
                                        font.family: "Segoe UI"
                                        color: "#ffffff"

                                        background: Rectangle {
                                            color: isEditMode ? "#2d3748" : "#4a5568"
                                            border.color: emailField.activeFocus ? "#68d391" : "#718096"
                                            border.width: 2
                                            radius: 10
                                        }
                                    }
                                }

                                // Phone Field
                                Column {
                                    width: parent.width
                                    spacing: 8

                                    Text {
                                        text: "Phone Number"
                                        font.bold: true
                                        font.pixelSize: 14
                                        color: "#e2e8f0"
                                        font.family: "Segoe UI"
                                    }

                                    TextField {
                                        id: phoneField
                                        width: parent.width
                                        height: 45
                                        text: accountWindow.phone
                                        enabled: isEditMode
                                        font.pixelSize: 15
                                        font.family: "Segoe UI"
                                        color: "#ffffff"

                                        background: Rectangle {
                                            color: isEditMode ? "#2d3748" : "#4a5568"
                                            border.color: phoneField.activeFocus ? "#68d391" : "#718096"
                                            border.width: 2
                                            radius: 10
                                        }
                                    }
                                }

                                // Address Field
                                Column {
                                    width: parent.width
                                    spacing: 8

                                    Text {
                                        text: "Address"
                                        font.bold: true
                                        font.pixelSize: 14
                                        color: "#e2e8f0"
                                        font.family: "Segoe UI"
                                    }

                                    TextField {
                                        id: addressField
                                        width: parent.width
                                        height: 45
                                        text: accountWindow.address
                                        enabled: isEditMode
                                        font.pixelSize: 15
                                        font.family: "Segoe UI"
                                        color: "#ffffff"

                                        background: Rectangle {
                                            color: isEditMode ? "#2d3748" : "#4a5568"
                                            border.color: addressField.activeFocus ? "#68d391" : "#718096"
                                            border.width: 2
                                            radius: 10
                                        }
                                    }
                                }

                                // Edit/Save Button
                                Button {
                                    id: editButton
                                    text: isEditMode ? "💾 Save Changes" : "✏️ Edit Profile"
                                    width: parent.width
                                    height: 50
                                    font.bold: true
                                    font.pixelSize: 15
                                    font.family: "Segoe UI"

                                    background: Rectangle {
                                        color: isEditMode ? "#48bb78" : "#68d391"  // Green theme
                                        radius: 12

                                        Rectangle {
                                            width: parent.width
                                            height: parent.height
                                            anchors.centerIn: parent
                                            anchors.verticalCenterOffset: editButton.pressed ? 0 : -2
                                            color: "#00000020"
                                            radius: parent.radius
                                            z: parent.z - 1
                                            visible: !editButton.pressed
                                        }
                                    }

                                    contentItem: Text {
                                        text: editButton.text
                                        font: editButton.font
                                        color: "#ffffff"
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                    }

                                    onClicked: {
                                        if (isEditMode) {
                                            // Save changes to the C++ properties before calling the update function
                                            accountWindow.phone = phoneField.text
                                            accountWindow.email = emailField.text
                                            accountWindow.address = addressField.text
                                            accountWindow.updateUserData() // Call the C++ database update function
                                            console.log("Saving changes to C++ properties.")
                                        }
                                        isEditMode = !isEditMode
                                    }
                                }
                            }
                        }
                    }

                    // Right Column - Contact Details
                    Rectangle {
                        id: contactCard
                        width: (parent.width - parent.spacing) / 2
                        height: 700
                        color: "#4a5568"  // Dark card background
                        radius: 20
                        border.color: "#68d391"  // Green border
                        border.width: 1

                        // Shadow effect
                        Rectangle {
                            width: parent.width
                            height: parent.height
                            anchors.centerIn: parent
                            anchors.verticalCenterOffset: 4
                            color: "#00000025"
                            radius: parent.radius
                            z: parent.z - 1
                        }

                        Column {
                            anchors.fill: parent
                            anchors.margins: 30
                            spacing: 25

                            Text {
                                text: "Contact Details"
                                font.bold: true
                                font.pixelSize: 24
                                color: "#ffffff"  // White text
                                font.family: "Segoe UI"
                            }

                            // Contact Information
                            Column {
                                width: parent.width
                                spacing: 25

                                // Phone Number
                                Rectangle {
                                    width: parent.width
                                    height: 80
                                    color: "#2d3748"  // Darker background
                                    radius: 15
                                    border.color: "#68d391"
                                    border.width: 1

                                    Row {
                                        anchors.left: parent.left
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.leftMargin: 20
                                        spacing: 15

                                        Rectangle {
                                            width: 40
                                            height: 40
                                            radius: 20
                                            color: "#68d391"  // Green icon background
                                            anchors.verticalCenter: parent.verticalCenter

                                            Text {
                                                anchors.centerIn: parent
                                                text: "📱"
                                                font.pixelSize: 18
                                            }
                                        }

                                        Column {
                                            anchors.verticalCenter: parent.verticalCenter
                                            spacing: 5

                                            Text {
                                                text: "Phone Number"
                                                font.bold: true
                                                font.pixelSize: 14
                                                color: "#e2e8f0"
                                                font.family: "Segoe UI"
                                            }

                                            Text {
                                                text: accountWindow.phone
                                                font.pixelSize: 16
                                                color: "#ffffff"
                                                font.family: "Segoe UI"
                                            }
                                        }
                                    }

                                    MouseArea {
                                        anchors.fill: parent
                                        cursorShape: Qt.PointingHandCursor
                                        onClicked: {
                                            Qt.openUrlExternally("tel:" + accountWindow.phone)
                                        }
                                    }
                                }

                                // Email
                                Rectangle {
                                    width: parent.width
                                    height: 80
                                    color: "#2d3748"
                                    radius: 15
                                    border.color: "#68d391"
                                    border.width: 1

                                    Row {
                                        anchors.left: parent.left
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.leftMargin: 20
                                        spacing: 15

                                        Rectangle {
                                            width: 40
                                            height: 40
                                            radius: 20
                                            color: "#68d391"
                                            anchors.verticalCenter: parent.verticalCenter

                                            Text {
                                                anchors.centerIn: parent
                                                text: "✉️"
                                                font.pixelSize: 18
                                            }
                                        }

                                        Column {
                                            anchors.verticalCenter: parent.verticalCenter
                                            spacing: 5

                                            Text {
                                                text: "Email Address"
                                                font.bold: true
                                                font.pixelSize: 14
                                                color: "#e2e8f0"
                                                font.family: "Segoe UI"
                                            }

                                            Text {
                                                text: accountWindow.email
                                                font.pixelSize: 16
                                                color: "#ffffff"
                                                font.family: "Segoe UI"
                                            }
                                        }
                                    }

                                    MouseArea {
                                        anchors.fill: parent
                                        cursorShape: Qt.PointingHandCursor
                                        onClicked: {
                                            Qt.openUrlExternally("mailto:" + accountWindow.email)
                                        }
                                    }
                                }

                                // Address
                                Rectangle {
                                    width: parent.width
                                    height: 80
                                    color: "#2d3748"
                                    radius: 15
                                    border.color: "#68d391"
                                    border.width: 1

                                    Row {
                                        anchors.left: parent.left
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.leftMargin: 20
                                        spacing: 15

                                        Rectangle {
                                            width: 40
                                            height: 40
                                            radius: 20
                                            color: "#68d391"
                                            anchors.verticalCenter: parent.verticalCenter

                                            Text {
                                                anchors.centerIn: parent
                                                text: "📍"
                                                font.pixelSize: 18
                                            }
                                        }

                                        Column {
                                            anchors.verticalCenter: parent.verticalCenter
                                            spacing: 5

                                            Text {
                                                text: "Address"
                                                font.bold: true
                                                font.pixelSize: 14
                                                color: "#e2e8f0"
                                                font.family: "Segoe UI"
                                            }

                                            Text {
                                                text: accountWindow.address
                                                font.pixelSize: 16
                                                color: "#ffffff"
                                                font.family: "Segoe UI"
                                            }
                                        }
                                    }
                                }

                                // Emergency Support
                                Rectangle {
                                    width: parent.width
                                    height: 80
                                    color: "#2d3748"
                                    radius: 15
                                    border.color: "#e53e3e"  // Red border for emergency
                                    border.width: 1

                                    Row {
                                        anchors.left: parent.left
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.leftMargin: 20
                                        spacing: 15

                                        Rectangle {
                                            width: 40
                                            height: 40
                                            radius: 20
                                            color: "#e53e3e"  // Red for emergency
                                            anchors.verticalCenter: parent.verticalCenter

                                            Text {
                                                anchors.centerIn: parent
                                                text: "🚨"
                                                font.pixelSize: 18
                                            }
                                        }

                                        Column {
                                            anchors.verticalCenter: parent.verticalCenter
                                            spacing: 5

                                            Text {
                                                text: "Emergency Support"
                                                font.bold: true
                                                font.pixelSize: 14
                                                color: "#e2e8f0"
                                                font.family: "Segoe UI"
                                            }

                                            Text {
                                                text: "+977-01-4123456"
                                                font.pixelSize: 16
                                                color: "#ffffff"
                                                font.family: "Segoe UI"
                                            }
                                        }
                                    }

                                    MouseArea {
                                        anchors.fill: parent
                                        cursorShape: Qt.PointingHandCursor
                                        onClicked: {
                                            Qt.openUrlExternally("tel:+977-01-4123456")
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // Footer - Dark theme
        Rectangle {
                id: footer
                width: parent.width
                height: 40
                color: "#2d3748"  // Dark footer
                border.color: "#68d391"
                border.width: 1
                anchors.bottom: parent.bottom

                Text {
                    anchors.centerIn: parent
                    text: "© 2025 Hamro Bus Sewa - Your Journey, Our Priority | Version - Beta"
                    color: "#e2e8f0"  // Light text
                    font.pixelSize: 12
                    font.family: "Segoe UI"
                }
            }
    }
}
