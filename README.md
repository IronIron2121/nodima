# ```<head>nodima</head>```

This experiment generates melodies and harmonies by use of different functions; primarily functions of distance, probability, and exponentiation. This is as much as I could fit in the included description; comments have been left in the code.

# How do I run it?

Just load it in to the openFrameworks projectGenerator and include ofxMaxim as an add-on

# How does it work?

The core functionality is composed of three main classes

1.	ScaleTransposer
2.	NoteNode
3.	Anima

## Scale Transposer
The ScaleTransposer allows a user to select a scale, and a desired range, based on a given scale and root note. It establishes class forms the basic musical context of a given run of the program. 

## NoteNode
This class is simple. Its objects lay out a two-dimensional grid where each column signifies a note, and each row an octave. A specific point on this grid therefore denotes a particular note within a specific octave. Each note holds attributes describing its location in the larger noteNodeVector and the Hz value of its note.

## Anima
On initialisation, an Anima is placed at a random node. On every beat, an Anima emits the note of its current Node, and has a chance of moving to another one. Its chance of moving depends on parameters described as emotional attributes like "boredom" and "patience". These parameters also determine the speed/BPM at which an Anima plays notes. An exponential function means that the rate of acceleration is always increasing, until it resets.
The choice of Node when moving is computed by a softmax function that takes the Manhattan (orthogonal) distances of the noteNodeVector as input, making distant and diagonal nodes more attractive than adjacent ones, mirroring an adventurous spirit.
Finally, when restlessness has increased past a certain point, the "Pineal" mode is activated. This mode frees the Anima from the constraints of its initial scale, allowing it to play a note from any of the list of available scales.


# Scales

The following scales are available and can be chosen from at lines 43 - 46 in ofApp.cpp

```
// set up the scale and the octaves
currentRootNote = "C";
currentScaleName = "Hijaz";
currentScale = scaleTransposer.transpose(currentRootNote, currentScaleName);
octaves 	 = 3;
```


```
this->availableScales = {
	"Major",
	"Minor",
	"Lydian",
	"Blues",
	"Hijaz",
	"Dorian",
	"Phrygian",
	"Diminished"
};
```