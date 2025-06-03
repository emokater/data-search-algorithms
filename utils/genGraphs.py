import pandas as pd
import matplotlib.pyplot as plt

data = {
    "Size": [],

    "Linear search": [],
    "Binary search tree": [],
    "RB tree": [],
    "Hash table": [],
    "Multimap": [],

    "Collisions": []
}

collisions = 5;

def parse_file(filepath, data):
    with open(filepath, "r") as f:
        lines = f.readlines()
        size = 0

        for line in lines:
            if not line:
                continue

            if line.startswith("Datasets"):
                size_str = line[len("Datasets"):-2]
                size = int(size_str)
                data["Size"].append(size)

            elif line[0] in "12345":
                _, time_str = line.split(": ")
                time = float(time_str)
                if line[0] == "1":
                    data["Linear search"].append(time)
                elif line[0] == "2":
                    data["Binary search tree"].append(time)
                elif line[0] == "3":
                    data["RB tree"].append(time)
                elif line[0] == "4":
                    data["Hash table"].append(time)
                elif line[0] == "5":
                    data["Multimap"].append(time)
            
            elif line.startswith("Collisions"):
                _, collis_str = line.split(": ")
                collis = int(collis_str)
                data["Collisions"].append(collis)

def plotCollis(data):
    plt.figure(figsize=(10, 6))
    plt.plot(data["Size"], data["Collisions"], color="blue")
    plt.xlabel("Dataset size")
    plt.ylabel("Count of collisions")
    plt.title("Hash and collisions")
    plt.legend()
    plt.grid(True)
    plt.show()

def plotAll(data):
    plt.figure(figsize=(10, 6))

    plt.plot(data["Size"], data["Linear search"], label="linear", color="blue")
    plt.plot(data["Size"], data["Binary search tree"], label="binary", color="red")
    plt.plot(data["Size"], data["RB tree"], label="rb", color="green")
    plt.plot(data["Size"], data["Hash table"], label="hash", color="purple")
    plt.plot(data["Size"], data["Multimap"], label="multimap", color="orange")

    plt.xlabel("Dataset size")
    plt.ylabel("Time of search")

    plt.xscale("log")
    plt.yscale("log")

    
    plt.title("All algorithms")
    plt.legend()
    plt.grid(True)
    plt.show()


parse_file("/Users/ekaterinagridneva/Desktop/hse/mp/data-search-algorithms/info_time.txt", data)
plotCollis(data)
plotAll(data)
