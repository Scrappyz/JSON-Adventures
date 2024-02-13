## About This Project
A customizable text-based adventure game using json files.

## Table of Content

## Usage
```
{
    "scenario": "You wake up with the sound of your alarm.\nIt is 8am, you need to go to school.",
    "gameOver": false,
    "choices": {
        "sleep": "sleep.json",
        "up": "get_up.json",
        "stand": "get_up.json"
    },
    "excuses": [
        "Maybe another time.",
        "You are too tired to do that."
    ]
}
```

You can create your own text-based adventure game by formatting your json files like this. The `scenario` is what will be happening currently. `gameOver` specifies if the that current scenario is a dead end. `choices` are the substrings that are needed to be in the input to go to the next scenario. For example, if the input string in this scenario has a `sleep` substring, you will move on to the next scenario in `sleep.json`. Finally, we have the `excuses`. These will be the output if the input string is none of the choices.