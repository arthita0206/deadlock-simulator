Deadlock Simulator & Visualization Tool
A comprehensive web-based application for simulating and visualizing deadlock handling algorithms in operating systems, including Banker's Algorithm, Deadlock Detection, and Resource Allocation Graph (RAG) cycle detection.

🚀 Features
Interactive Web Interface (Streamlit)

Multiple Algorithm Support:

Banker's Algorithm (Deadlock Avoidance)

Deadlock Detection Algorithm

RAG Cycle Detection with Wait-for Graph visualization

Visual Graph Representation using Graphviz

Cycle Highlighting: Red highlighting for detected cycles and deadlocked processes

Matrix Input Validation and user-friendly error checking

🛠️ Technologies Used
Python (core implementation and web framework)

Streamlit (interactive web interface)

NumPy (matrix operations and calculations)

Graphviz (graph visualization and rendering)

C (original algorithm implementations included for reference)

📋 Prerequisites
Python 3.7+

pip package manager

⚙️ Installation
Clone the repository:

text
git clone https://github.com/yourusername/deadlock-simulator.git
cd deadlock-simulator
Install requirements:

text
pip install streamlit numpy graphviz
🚦 Usage
Run the application:

text
streamlit run deadlock_webapp.py
Access the app in your browser (typically at http://localhost:8501)

Select operations from the sidebar, enter matrices, and visualize or analyze deadlocks.

📊 Algorithm Details
Banker's Algorithm

Deadlock avoidance using system safety checks and displays safe sequence.

Deadlock Detection

Detects deadlocked processes for the current state using classic OS detection logic.

RAG Cycle Detection

Visualizes the wait-for graph and highlights any cycles to indicate potential deadlocks.

📁 Project Structure
text
deadlock-simulator/
├── deadlock_webapp.py    # Main Streamlit application
├── banker.c              # Original C implementation of Banker's Algorithm
├── detection.c           # Original C implementation of Deadlock Detection
├── rag.c                 # Original C implementation of RAG operations
├── graph.c               # Graph data structure implementation
├── main.c                # Main C program entry point
├── README.md             # Project documentation
└── requirements.txt      # Python dependencies (optional)

🔮 Future Enhancements
Add coloring/highlighting for cycles and deadlocked nodes in visual graphs

Implement animated step-by-step execution of algorithms

Enable interactive grid/table-based input for matrices

Allow user to save and load scenarios

Support for resources with multiple instances

Deadlock resolution/suggestion engine

Exportable reports

Mobile and multi-user features

Further optimize for large scale

Guided tutorial mode for OS learning

🤝 Contributing
Fork this repository

Create your branch (git checkout -b feature/AmazingFeature)

Commit your changes (git commit -m 'Add some AmazingFeature')

Push to the branch (git push origin feature/AmazingFeature)

Open a Pull Request

📄 License
This project is licensed under the MIT License - see the LICENSE file for details.

👨‍💻 Author
Your Name - @arthita0206
