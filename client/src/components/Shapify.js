import * as React from 'react';
import ReactDOM from 'react-dom';

import Box from '@mui/material/Box';
import Typography from '@mui/material/Typography';
import Button from '@mui/material/Button';

import { red, pink, purple, deepPurple, indigo, blue, lightBlue, cyan, teal, green, lightGreen, lime, yellow, amber, orange, deepOrange, brown, grey, blueGrey } from '@mui/material/colors';

//to use: <ColorMatch handler={handleSolve}>
function Shapify(props){
    //const [solved, setSolved] = React.useState(-1); //-1: not acted, 0: incorrect, 1: correct
    // const colors = ["error", "warning", "success", "primary", "secondary"];
    const colors = [red[500], orange[500], yellow[600], green[500], blue[500], purple[500]];
    const words = ["Red", "Orange", "Yellow", "Green", "Blue", "Purple"];
    const types = ["Word", "Color"];
    const game = props['info']['game']
    let type = Math.floor(Math.random()*2);

    console.log(props['info'])

    let colorA = words.indexOf(game['colors'][0]); // Math.floor(Math.random()*6);
    let colorB = words.indexOf(game['colors'][1]); // Math.floor(Math.random()*5);
    /*
    if(colorB >= colorA){
      colorB ++;
    }
    */
    let targetWords = [words[colorA], words[colorB]];
    let targetColors = [colors[colorA], colors[colorB]];

    let target = game['target']; 
    //<div>{ JSON.stringify(props['info']) }</div>

    return (
      <div>
          <Typography variant="h6" sx={{ mb: 2 }}>Choose { game['type'] } { target }</Typography>

          <Box sx={{ display: 'flex', flexWrap: 'wrap', justifyContent: 'space-evenly' }}>
              <Box sx={{ backgroundColor: colors[colorA], color: '#ffffff',  width: 1/3, m: 1, p: 3, textAlign: 'center' }}>
                  <Typography variant="h5">{words[colorB]}</Typography>
              </Box>

              <Box sx={{ backgroundColor: colors[colorB], color: '#ffffff', width: 1/3, m: 1, p: 3, textAlign: 'center' }}>
                  <Typography variant="h5">{words[colorA]}</Typography>
              </Box>
          </Box>
      </div>
    );
}
export default Shapify;
