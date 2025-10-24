import streamlit as st
import graphviz

st.sidebar.title("Menu")
mode = st.sidebar.selectbox(
    "Select Operation",
    ["Graph Visualization", "Banker's Algorithm", "Deadlock Detection", "RAG Cycle Detection"]
)

if mode == "Graph Visualization":
    st.header("Graph Visualization")
    processes = st.number_input("Number of Processes", min_value=1, value=3, key="gv_proc")
    resources = st.number_input("Number of Resources", min_value=1, value=2, key="gv_res")
    alloc_str = st.text_area("Allocation Matrix", "2 1\n1 0\n0 1", key="gv_alloc")
    max_str = st.text_area("Max Matrix", "3 2\n1 2\n1 3", key="gv_max")
    alloc_rows = [list(map(int, r.split())) for r in alloc_str.strip().split('\n')]
    max_rows = [list(map(int, r.split())) for r in max_str.strip().split('\n')]
    dot_str = "digraph RAG {\n"
    for i in range(processes):
        for j in range(resources):
            if alloc_rows[i][j] > 0:
                dot_str += f"R{j} -> P{i};\n"
    for i in range(processes):
        for j in range(resources):
            if max_rows[i][j] - alloc_rows[i][j] > 0:
                dot_str += f"P{i} -> R{j};\n"
    dot_str += "}"
    st.graphviz_chart(dot_str)

elif mode == "Banker's Algorithm":
    st.header("Banker's Algorithm")
    processes = st.number_input("Number of Processes", min_value=1, value=3, key="bk_proc")
    resources = st.number_input("Number of Resources", min_value=1, value=2, key="bk_res")
    alloc_str = st.text_area("Allocation Matrix", "2 1\n1 0\n0 1", key="bk_alloc")
    max_str = st.text_area("Max Matrix", "3 2\n1 2\n1 3", key="bk_max")
    available_str = st.text_area("Available Vector", "2 1", key="bk_avail")

    if st.button("Run Banker's Algorithm", key="btn_banker"):
        import numpy as np

        # Convert inputs to proper matrices
        alloc_rows = [list(map(int, r.split())) for r in alloc_str.strip().split('\n')]
        max_rows = [list(map(int, r.split())) for r in max_str.strip().split('\n')]
        available = list(map(int, available_str.strip().split()))
        processes_count = int(processes)
        resources_count = int(resources)
        allocation = np.array(alloc_rows)
        max_matrix = np.array(max_rows)
        need = max_matrix - allocation
        work = np.array(available)
        finish = [False] * processes_count
        safe_sequence = []

        while len(safe_sequence) < processes_count:
            made_progress = False
            for i in range(processes_count):
                if not finish[i] and all(need[i][j] <= work[j] for j in range(resources_count)):
                    work = work + allocation[i]
                    finish[i] = True
                    safe_sequence.append(f"P{i}")
                    made_progress = True
            if not made_progress:
                break

        if len(safe_sequence) == processes_count:
            st.success(f"System is in a safe state.\nSafe sequence: {' → '.join(safe_sequence)}")
        else:
            st.error("System is NOT in a safe state. No complete safe sequence found.")

elif mode == "Deadlock Detection":
    st.header("Deadlock Detection")
    processes = st.number_input("Number of Processes", min_value=1, value=3, key="dl_proc")
    resources = st.number_input("Number of Resources", min_value=1, value=2, key="dl_res")
    alloc_str = st.text_area("Allocation Matrix", "2 1\n1 0\n0 1", key="dl_alloc")
    request_str = st.text_area("Request Matrix", "1 1\n0 2\n1 2", key="dl_req")
    available_str = st.text_area("Available Vector", "2 1", key="dl_avail")

    if st.button("Run Deadlock Detection", key="btn_detect"):
        import numpy as np

        # Convert input strings to matrices
        allocation = np.array([list(map(int, r.split())) for r in alloc_str.strip().split('\n')])
        request = np.array([list(map(int, r.split())) for r in request_str.strip().split('\n')])
        available = np.array(list(map(int, available_str.strip().split())))
        n_processes = int(processes)
        n_resources = int(resources)

        work = available.copy()
        finish = []
        for i in range(n_processes):
            has_allocation = any(allocation[i][j] != 0 for j in range(n_resources))
            finish.append(1 if not has_allocation else 0)

        found = True
        while found:
            found = False
            for i in range(n_processes):
                if finish[i] == 0:
                    if all(request[i][j] <= work[j] for j in range(n_resources)):
                        work += allocation[i]
                        finish[i] = 1
                        found = True

        deadlocked_processes = [f"P{i}" for i in range(n_processes) if finish[i] == 0]

        if deadlocked_processes:
            st.error(f"Deadlock detected!\nDeadlocked processes: {' '.join(deadlocked_processes)}")
        else:
            st.success("No deadlock detected. The system is safe.")


elif mode == "RAG Cycle Detection":
    st.header("RAG Cycle Detection (Wait-for Graph Based)")
    processes = st.number_input("Number of Processes", min_value=1, value=3, key="rag_proc")
    resources = st.number_input("Number of Resources", min_value=1, value=2, key="rag_res")
    alloc_str = st.text_area("Allocation Matrix", "2 1\n1 0\n0 1", key="rag_alloc")
    request_str = st.text_area("Request Matrix", "1 1\n0 2\n1 2", key="rag_req")
    available_str = st.text_area("Available Vector", "2 1", key="rag_avail")

    if st.button("Run RAG Cycle Detection", key="btn_rag"):
        import numpy as np

        n_proc = int(processes)
        n_res = int(resources)

        allocation = np.array([list(map(int, r.split())) for r in alloc_str.strip().split('\n')])
        request = np.array([list(map(int, r.split())) for r in request_str.strip().split('\n')])
        available = np.array(list(map(int, available_str.strip().split())))

        # Build Wait-for Graph (WFG)
        adj = {f"P{i}": [] for i in range(n_proc)}
        for i in range(n_proc):
            for r in range(n_res):
                if request[i][r] > 0 and available[r] < request[i][r]:
                    for j in range(n_proc):
                        if allocation[j][r] > 0:
                            adj[f"P{i}"].append(f"P{j}")

        # ---------- Cycle Detection with Path Tracking ----------
        def find_cycle_path(adj):
            path = []
            visited = set()
            stack = []
            finished = set()
            result = []
            def dfs(node):
                visited.add(node)
                stack.append(node)
                for nbr in adj[node]:
                    if nbr not in visited:
                        if dfs(nbr):
                            return True
                    elif nbr in stack:
                        idx = stack.index(nbr)
                        # cycle found
                        result.extend(stack[idx:] + [nbr])
                        return True
                stack.pop()
                finished.add(node)
                return False
            for v in adj:
                if v not in visited and dfs(v):
                    return result
            return []
        cycle_path = find_cycle_path(adj)
        highlight_edges = set()
        # collect the edges in the detected cycle only (as tuples)
        if cycle_path:
            for i in range(len(cycle_path) - 1):
                highlight_edges.add((cycle_path[i], cycle_path[i + 1]))

        # --- Wait-for Graph Visualization with coloring ---
        dot_str = "digraph WFG {\n"
        for u in adj:
            for v in adj[u]:
                if (u, v) in highlight_edges:
                    dot_str += f'  {u} -> {v} [color=red, penwidth=2];\n'
                else:
                    dot_str += f'  {u} -> {v};\n'
        dot_str += "}"
        st.subheader("Wait-for Graph (WFG)")
        st.graphviz_chart(dot_str)

        # --- Cycle/Deadlock result ---
        if cycle_path:
            st.error("Cycle detected in Wait-for Graph → Deadlock may exist. (Red edges highlight the cycle)")
        else:
            st.success("No cycle detected in Wait-for Graph → System is not deadlocked.")
