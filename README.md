# Dynamic Scheduling Strategy for Intelligent RGV

An intelligent processing system is composed of 8 computer number controller (CNC) machines, one automatic Rail Guide Vehicle (RGV) with straight line track, one incoming belts, one discharge belts and other auxiliary equipment. RGV is a self-driving intelligent vehicle, which can run freely on fixed tracks. RGV can automatically control the direction and distance of movement according to instructions. RGV is able to complete loading and unloading and cleaning operations

![image](https://i.loli.net/2018/09/17/5b9fa1b0848e6.jpg)

**For the following situation：**

Material is processed in one process: each CNC is equipped with the same tool, and the material can be processed on any CNC.

**The task is:**

For general processing problem, formulate the RGV dynamic scheduling model and give the corresponding algorithm.

## The operation parameters of the intelligent processing system

| The Operation Parameters of the System | First Set | Second Set | Third Set |
| --- | --- | --- | --- |
| RGV move one unit time | 20 | 23 | 18 |
| RGV move two units time | 33 | 41 | 32 |
| RGV move three units time | 46 | 59 | 46 |
| One process: CNC processing time of a material | 560 | 580 | 545 |
| Two processes: CNC processing sequence 1 time of a material | 400 | 280 | 455 |
| Two processes: CNC processing sequence 2 time of a material | 378 | 500 | 182 |
| RGV time of one loading and unloading to CNC1#,3#,5#,7# | 28 | 30 | 27 |
| RGV time of one loading and unloading to CNC2#,4#,6#,8# | 31 | 35 | 32 |
| RGV cleaning and carrying out delivery time of a material | 25 | 30 | 25 |

**8 hours of continuous operation for each working shift.**

## Description of the system scene and physical pictures

In picture 1, the middle equipment is RGV with cleaning tank and manipulator. The cleaning tank can clean one material every time. There are two paws in the front of the manipulator’s arm, paws can grab one material successively by rotating to complete loading-unloading operation. The 8 CNCs are arranged in the two sides of the picture 1. There is a piece of conveyer belt installed in front of each CNC. The right side of picture 1 is the loading conveyor belt, which is responsible for conveying raw material for CNC, and the left of the picture 1 is the unloading conveyor belt, which is responsible for sending the processed and cleaned material out of the system. Other auxiliary equipment helps the system for its normal operation. 

![image](https://i.loli.net/2018/09/17/5b9fa1b0e0706.jpg)
Picture 1：RGV—CNC workshop layout

![image](https://i.loli.net/2018/09/17/5b9fa1b0e0cf0.jpg)
Picture 2：RGV which carried-self paws and cleaning tank
 
![image](https://i.loli.net/2018/09/17/5b9fa1b147db9.jpg)
![image](https://i.loli.net/2018/09/17/5b9fa1b04a8aa.jpg)
Picture 3：Two paws and their operation in the front of RGV manipulator’s arm

In the left of picture 3, unprocessed raw material A was grasped by the upper paw of the arm, there is a processed material B on the CNC table. The empty paw (lower part of the arm) is ready to grab the processed material B. The RGV manipulator will complete the unloading operation after grabbed the processed B.
In the right of picture 3, the lower paw of the arm has captured B, the manipulator raises its arm and rotates the hand, the raw material A is aligned to the processing position and placed on the CNC table, and then RGV manipulator has completed the loading operation.

## The composition and explanation of the intelligent processing system

An intelligent processing system is composed of 8 CNC machines, one Rail Guide Vehicle (RGV) which carried-self manipulator and cleaning tank, one straight line track of RGV, one incoming belts, one discharge belts and other auxiliary equipment.

**（1）CNC**：4 sets CNC are arranged on both sides of the incoming belts and the discharge belts, and equidistant arrangement. Each CNC can only be equipped with one tool and processes one material.

If the material processing needs two processes, it needs different CNC to install different tools to complete the processing. The tool cannot be changed in the process of processing. The first and second processes need to be completed successively on different CNC, each CNC can only complete one process, and the processed time of the two processes is different.

**（2）RGV**：RGV has intelligent control function, can receive and send command signals. According to the instruction, RGV can move in the straight line or stop to wait. RGV can move 1 units (the distance between two adjoining CNCs), or move two units (the distance of three adjoining CNCs), or move three units (the distance of adjoining four CNCs), if two CNCs are aligned relative to each other, their distance is zero. At the same time, RGV can only execute a command such as moving, waiting, loading and unloading, cleaning operation, etc.

**（3）Loading conveyor belts**：Loading conveyor belt consists of 4 segments. There is a segment belt on each odd numbered CNC1#, 3#, 5#, 7#. Loading belts are controlled by the system sensor, it moves (roll) in one direction, not only transfer motion together, but also transfer motion independently.

**（4）Unloading conveyor belts**：Unloading conveyor belt consists of 4 segments also. There is a segment belt on each even numbered CNC2#, 4#, 6#, 8#. Unloading belt’s motion is the same as that of loading belts.

##  The operating process of the system

（1）At the time the intelligent machining system turns on, the initial position of RGV is between CNC1# and CNC2#, and all CNCs are idle.

（2）In the normal, if a CNC is in the idle state, the system sents the material demand signal to the RGV, otherwise, CNC is in the processing state, and the requirement signal is sent to the RGV immediately after its processing operation over. After receiving the demand signal of a CNC, RGV determines the order of CNC loading and unloading, then, RGV does the loading and unloading operation according to the order.

（3）According to the requirement instruction, RGV runs to an idle CNC, a raw material carried by loading belts arrived at this CNC at the same time, RGV will catch this raw material for loading. 

RGV loading and unloading time required for even numbered CNC is greater than that for odd numbered CNC.

（4）In fact, after the RGV has completed one loading and unloading for a certain CNC, the manipulator moves the processed material to the cleaning slot and cleans it (only cleaning processed material). 

Specific processes: First, manipulator takes out the cleaned material in the cleaning tank, and rotating claw, then put the processed material on another paw into the cleaning tank for cleaning. After that, manipulator moves the cleaned material and lay down it on the unloading conveyor belt to have it leave the system. The time required for this process is called the cleaning operation time of RGV. RGV cannot move during the cleaning process. 
The actual cleaning time of the processed material in the cleaning tank is very short, and it takes less time than the manipulator to put the material on the unloading conveyor belt. 

（5）After RGV has finished a loading and unloading operation, it immediately executes the next instruction. RGV will wait for the next instruction at its place if it does not receive other CNC demand signals. 

After a CNC completes the processing of a material, it sends a demand signal to the RGV immediately. If the RGV does not arrive, the CNC will wait. 

（6）The system repeats step (3) to step (5) again and again until the system stops operation, and RGV goes back to its original position. 








 