import * as React from 'react';
import { useState } from 'react';
import ReactDOM from 'react-dom';

import Box from '@mui/material/Box';
import Typography from '@mui/material/Typography';
import Button from '@mui/material/Button';

import { red, pink, purple, deepPurple, indigo, blue, lightBlue, cyan, teal, green, lightGreen, lime, yellow, amber, orange, deepOrange, brown, grey, blueGrey } from '@mui/material/colors';

//to use: <ColorMatch handler={handleSolve}>
function ColorMatch(props){
    const colors = [red[500], orange[500], yellow[600], green[500], blue[500], purple[500]];
    const words = ["Red", "Orange", "Yellow", "Green", "Blue", "Purple"];
    const types = ["word", "color"];

    const [currentColorMatch, updateColorMatch] = useState({"colorIndexA": Math.floor(Math.random() * colors.length), 
    "colorIndexB": Math.floor(Math.random() * colors.length),
    "wordIndexA": Math.floor(Math.random() * colors.length),
    "wordIndexB": Math.floor(Math.random() * colors.length),
    "type": ["word", "color"][Math.floor(Math.random()*2)],
    "pos": Math.floor(Math.random()*2),
    "solved": false
});
    let colorIndexA = currentColorMatch["colorIndexA"];
    let colorIndexB = currentColorMatch["colorIndexB"];
    let wordIndexA = currentColorMatch["wordIndexA"];
    let wordIndexB = currentColorMatch["wordIndexB"];
    let type = currentColorMatch["type"];
    let pos = currentColorMatch["pos"];

    let targetName = words[wordIndexA];
    //testing
    type = "word";

    while (wordIndexA == wordIndexB) {
        wordIndexB = (wordIndexB + 2) % colors.length;
    }

    if (pos) {
        let temp = wordIndexA;
        wordIndexA = wordIndexB;
        wordIndexB = temp;
    }
  

    return (
      <div>
          <Typography variant="h6" sx={{ mb: 2 }}>Choose the { type }: { targetName }</Typography>

          <Box sx={{ display: 'flex', flexWrap: 'wrap', justifyContent: 'space-evenly' }}>
              <Box onClick={() => updateColorMatch({"colorIndexA": colorIndexA, "colorIndexB": colorIndexB, "wordIndexA": wordIndexA, "wordIndexB": wordIndexB, "type": type, "pos": 0, "solved": false})}
              sx={{ backgroundColor: colors[colorIndexA], color: '#ffffff',  width: 1/3, m: 1, p: 3, textAlign: 'center' }}>
                  <Typography variant="h5">{words[wordIndexA]}</Typography>
              </Box>

              <Box sx={{ backgroundColor: colors[colorIndexB], color: '#ffffff', width: 1/3, m: 1, p: 3, textAlign: 'center' }}>
                  <Typography variant="h5">{words[wordIndexB]}</Typography>
              </Box>
          </Box>
      </div>
    );
}
export default ColorMatch;
