# Final Project - The Wikipedia Link Game
By: sb30-vedantj2-ssbonde2 <br>
The goal is to let a user play the wikipedia game, where the goal is to find the shortest path between two seemingly-unrelated pages using hyperlinks within wikipedia articles. For example, a potential game might be to get to the page for 'University of Illinois at Urbana Champaign' to 'White House' - done by going to 'LEED', then 'Washington DC', then to 'White House'. <br>
In our game, the user enters/selects the start page and end page, and we provide the sequence of links to follow to link the endpoints (or we tell the user if doing so is impossible).

# How to run this project:
1. From within the data folder, run 'wget https://snap.stanford.edu/data/wiki-topcats.txt.gz' 
    and 'wget https://snap.stanford.edu/data/wiki-topcats-page-names.txt.gz'
2. Unzip the files using 'gzip -d wiki-topcats-page-names.txt.gz' and 'gzip -d wiki-topcats.txt.gz'
2. From the project home directory run 'make all'
3. Edit the data/test_input.txt file to use the data files you just downloaded and your desired start and end points, and set the output file if desired. After everything, your test_input.txt file should look something like this: <br> <br>
data/wiki-topcats-page-names.txt <br>
data/wiki-topcats.txt<br>
Michael Schumacher<br>
Valentino Rossi<br>
data/test_output.txt<br>

5. Run './pathfinder' to run the game. Add the '-test' flag to run the tests instead.

