import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__() #It allows the child class to invoke methods or attributes of its parent class, avoiding the need to refer to the parent class explicitly
        self.setWindowTitle("Step 2: Button")
        self.setGeometry(100, 100, 400, 300)

        # Add a button
        self.button = QPushButton("Click Me", self)
        self.button.setGeometry(150, 100, 100, 40)  # x, y, width, height

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
