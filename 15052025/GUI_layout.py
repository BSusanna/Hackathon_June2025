import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QVBoxLayout, QWidget
from PyQt5.QtCore import Qt

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Buttons with Spacing")
        self.setGeometry(100, 100, 800, 600)

        # Create a central widget
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        # Add a vertical layout
        layout = QVBoxLayout()
        central_widget.setLayout(layout)

        layout.setAlignment(Qt.AlignCenter)

        # Add buttons with spacing between each
        button1 = QPushButton("Button 1")
        button1.setFixedSize(200, 60)
        layout.addWidget(button1)
        layout.addSpacing(60)  # Add space after Button 1

        button2 = QPushButton("Button 2")
        button2.setFixedSize(200, 60)
        layout.addWidget(button2)
        layout.addSpacing(60)  # Add space after Button 2

        button3 = QPushButton("Button 3")
        button3.setFixedSize(200, 60)
        layout.addWidget(button3)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
