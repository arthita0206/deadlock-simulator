import graphviz
dot = graphviz.Source.from_file('rag.dot')
dot.render('rag_graph', view=True)
