import sys
import random
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QPushButton, QWidget
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure


class PlotCanvas(FigureCanvas):
    def __init__(self, parent=None, width=5, height=4, dpi=100):
        # Initialize the Matplotlib figure
        self.fig = Figure(figsize=(width, height), dpi=dpi)
        self.ax = self.fig.add_subplot(111)
        super().__init__(self.fig)
        self.setParent(parent)

        # Plot initial data
        self.plot_initial_data()

    def plot_initial_data(self):
        # Initial random data
        data = [random.randint(1, 10) for _ in range(10)]
        self.ax.clear()
        self.ax.plot(data, marker="o")
        self.ax.set_title("Random Data Plot")
        self.draw()

    def update_plot(self):
        # Generate new random data and update the plot
        data = [random.randint(1, 10) for _ in range(10)]
        self.ax.clear()
        self.ax.plot(data, marker="o")
        self.ax.set_title("Updated Random Data Plot")
        self.draw()


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Random Data Plotter")
        self.setGeometry(100, 100, 800, 600)

        # Central widget
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        # Layout
        layout = QVBoxLayout(central_widget)

        # Matplotlib plot canvas
        self.plot_canvas = PlotCanvas(self, width=5, height=4, dpi=100)
        layout.addWidget(self.plot_canvas)

        # Button to update the plot
        self.button = QPushButton("Generate New Data")
        self.button.clicked.connect(self.update_plot)
        layout.addWidget(self.button)

    def update_plot(self):
        # Call the update_plot method of the canvas
        self.plot_canvas.update_plot()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
