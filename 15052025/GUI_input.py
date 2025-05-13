import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QLineEdit, QPushButton, QLabel, QWidget

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Input Example")
        self.setGeometry(100, 100, 400, 200)

        # Create a central widget
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        # Create a vertical layout
        layout = QVBoxLayout()
        central_widget.setLayout(layout)

        # Add an input field
        self.input_field = QLineEdit()
        self.input_field.setPlaceholderText("Enter something...")
        layout.addWidget(self.input_field)

        # Add a label to display the result
        self.result_label = QLabel("Result will be shown here")
        layout.addWidget(self.result_label)

        # Add a button
        self.button = QPushButton("Submit")
        self.button.clicked.connect(self.process_input)
        layout.addWidget(self.button)

    def process_input(self):
        # Get the text from the input field
        user_input = self.input_field.text()

        # Perform an action based on the input
        if user_input.lower() == "hello":
            self.result_label.setText("You said hello!")
        elif user_input.isdigit():
            self.result_label.setText(f"You entered a number: {user_input}")
        else:
            self.result_label.setText(f"You said: {user_input}")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
