# My Main Three Projects from my Algorithms I Course!

## Project 1

Given a planar graph and the coordinates of its vertices, list all the faces of the graph.

## Project 2

A graph where edges represent roads and vertices represent cities. Each edge contains three values: the construction time for the road, the time to cross the road, and the cost of producing the road. The task is to determine:

- The minimum time to travel from the most important city to every other city.
- The time in years until all the shortest paths are completed.
- The time in years until it's possible to reach all cities from the central city, regardless of how long it takes.
- Finally, calculate the minimum cost to connect all cities.

## Project 3

This project involves a dynamic programming problem related to optimizing the traversal of a skatepark with multiple sections. The goal is to find the most radical sequence of skateboarding tricks that can be performed across the park's sections, considering various constraints and scoring rules.

- A skatepark has N sections where sequences of tricks can be performed (a sequence may be empty). Each section has a bonus factor ci and a crossing time ℓi.
- There are only K allowed tricks in the commune, each with a duration tj and a base score pj. Be cautious, as the base score can be negative!
- A trick can be performed at most once in each section of the skatepark (no spamming), and no trick can be performed partially; it must start and end within a section.
- If a trick is performed in two consecutive sections, its score is halved: ⌊pj/2⌋. For example, if pj = 5, the new score is 2. A trick performed in section i but not in section i + 1 retains its full score in section i + 2.
- The final score of a trick sequence ⟨m1, . . . , mr⟩ in a section with bonus factor ci is given by the sum of the scores of each of the r tricks multiplied by ci. For instance, if we perform tricks with scores ⟨1, ⌊7/2⌋, 2, 5⟩ in ci = 10, the total score is (1 + 3 + 2 + 5) * 10 * 4 = 440.
