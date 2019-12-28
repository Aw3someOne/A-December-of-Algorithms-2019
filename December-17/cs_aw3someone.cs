using System;
using System.Collections.Generic;
using System.Linq;

namespace December_17___Subway_Surfer {
	class Node {
		public readonly string name;
		public readonly List<Node> neighbors;
		public Node(string name) {
			this.name = name;
			neighbors = new List<Node>();
		}

		public void AddNeighbor(Node n) {
			neighbors.Add(n);
		}
	}

	class Program {
		// VERY unoptimized implementation of djikstra's algorithm
		static void Djikstra(Dictionary<string, Node> graph, Node source, Node target) {
			Dictionary<Node, int> dist = new Dictionary<Node, int>();
			Dictionary<Node, Node> prev = new Dictionary<Node, Node>();
			List<Node> queue = new List<Node>();
			foreach (var pair in graph) {
				var v = pair.Value;
				dist[v] = Int32.MaxValue;
				prev[v] = null;
				queue.Add(v);
			}
			dist[source] = 0;

			while (queue.Count > 0) {
				Node u = queue.Select(n => (dist[n], n.name, n)).Min().n;
				if (u == target) break; // we only care about distance to target

				queue.Remove(u);
				foreach (Node v in u.neighbors) {
					int alt = dist[u] + 1;
					if (alt < dist[v]) {
						dist[v] = alt;
						prev[v] = u;
					}
				}
			}

			var path = ReconstructPath(dist, prev, source, target);
			Console.WriteLine($"Shortest Path: {String.Join("->", path.Select(n => n.name))}");
		}

		static LinkedList<Node> ReconstructPath(Dictionary<Node, int> dist, Dictionary<Node, Node> prev, Node source, Node target) {
			LinkedList<Node> S = new LinkedList<Node>();
			Node u = target;
			if (prev[u] != null || u == source) {
				while (u != null) {
					S.AddFirst(u);
					u = prev[u];
				}
			}
			return S;
		}

		static void Main(string[] args) {
			Console.WriteLine("Enter Train Lines, Start and Endpoint");
			string[] input = new string[2];
			for (int i = 0; i < input.Length; i++) {
				Console.Write($"Line {i + 1}: ");
				input[i] = Console.ReadLine();
			}
			Console.Write("Start: ");
			string start = Console.ReadLine();
			Console.Write("End: ");
			string end = Console.ReadLine();

			List<List<string>> lines = input.Select(line => line.Split(',').Select(s => s.Trim()).ToList()).ToList();
			Dictionary<string, Node> nodes = new Dictionary<string, Node>();
			foreach (List<string> stops in lines)
				foreach (string s in stops)
					if (!nodes.ContainsKey(s))
						nodes.Add(s, new Node(s));

			foreach (List<string> stops in lines)
				for (int i = 0; i < stops.Count; i++) {
					string s = stops[i];
					Node n = nodes[s];
					if (i > 0)
						n.AddNeighbor(nodes[stops[i - 1]]);
					if (i < stops.Count - 1)
						n.AddNeighbor(nodes[stops[i + 1]]);
				}

			Djikstra(nodes, nodes[start], nodes[end]);
		}
	}
}
