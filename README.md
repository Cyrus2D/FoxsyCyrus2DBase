# Cyrus2D Base 
[![GitHub license](https://img.shields.io/github/license/helios-base/helios-base)](https://github.com/helios-base/helios-base/blob/master/LISENCE)

Cyrus2D-base is a sample team for the RoboCup Soccer 2D Simulator.
This base is a Helios base Fork.
We merged the newest version of Helios base(Agent2D) with the Gliders2D base V2.6 together,
After that we applied several features of Cyrus2021, the champion of RoboCup 2021 in Soccer Simulation 2D league to improve the performance and capabilities of this base.

This version of Cyrus2D Base is implemented for Foxsy AI project.

![The evolution of Helios2D, Glider2D and Cyrus2D base codes](https://github.com/Cyrus2D/Cyrus2DBase/blob/cyrus2d/cyrus-base.png)

All programs can work with rcssserver-18.

- The RoboCup Soccer Simulator: http://github.com/rcsoccersim/
- RoboCup Official Homepage: http://www.robocup.org/

## Quick Start

Download latest version "cyrus.zip" from https://github.com/Cyrus2D/FoxsyCyrus2DBase/releases

Extract "cyrus.zip"

Run "start.sh" with the following parameters:
- -t: team name
- -p: player port number (coach port number = player port number + 2)
- -c: config path (path should be directory and in the directory config.json should be exist)
- -j: json config

### Examples

```bash
./start.sh -t Test -p 6000 -c ~/Data/1

./start.sh -t Test -p 6000 -c ~/Data/1/f.config

./start.sh -t Test -p 6000 -c ~/Data/1/

./start.sh -t Test -p 6000 -j '{"formation_name":"433"}'
```

### Json Settings

- `formation_name`: name of formation (default: "433") options "433", "433l"
- 
## References

The paper about Cyrus2D Base:
- Zare N, Amini O, Sayareh A, Sarvmaili M, Firouzkouhi A, Rad SR, Matwin S, Soares A. Cyrus2D Base: Source Code Base for RoboCup 2D Soccer Simulation League. InRoboCup 2022: Robot World Cup XXV 2023 Mar 24 (pp. 140-151). Cham: Springer International Publishing.
- Zare N, Sarvmaili M, Sayareh A, Amini O, Matwin S, Soares A. Engineering Features to Improve Pass Prediction in Soccer Simulation 2D Games. InRobot World Cup 2022 (pp. 140-152). Springer, Cham.
- Zare N, Amini O, Sayareh A, Sarvmaili M, Firouzkouhi A, Matwin S, Soares A. Improving Dribbling, Passing, and Marking Actions in Soccer Simulation 2D Games Using Machine Learning. InRobot World Cup 2021 Jun 22 (pp. 340-351). Springer, Cham.

The paper about HELIOS Base:
- Hidehisa Akiyama, Tomoharu Nakashima, HELIOS Base: An Open Source
Package for the RoboCup Soccer 2D Simulation, In Sven Behnke, Manuela
Veloso, Arnoud Visser, and Rong Xiong editors, RoboCup2013: Robot
World XVII, Lecture Notes in Artificial Intelligence, Springer Verlag,
Berlin, 2014. http://dx.doi.org/10.1007/978-3-662-44468-9_46

The paper about Gliders2D Base:
- M. Prokopenko, P. Wang, Fractals2019: Combinatorial Optimisation with Dynamic Constraint Annealing, RoboCup 2019: Robot World Cup XXIII, 616-630 (Champion paper), Springer-Verlag, 2019;  also: arXiv:1909.01788, 2019.
- M. Prokopenko, P. Wang,  Gliders2d: Source Code Base for RoboCup 2D Soccer Simulation League, RoboCup 2019: Robot World Cup XXIII, 418-428, Springer-Verlag, 2019;  also:  arXiv:1812.10202, 2018.