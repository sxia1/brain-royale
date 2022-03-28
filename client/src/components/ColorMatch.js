import * as React from 'react';
import ReactDOM from 'react-dom';

import Button from '@mui/material/Button';

import { red, pink, purple, deepPurple, indigo, blue, lightBlue, cyan, teal, green, lightGreen, lime, yellow, amber, orange, deepOrange, brown, grey, blueGrey } from '@mui/material/colors';

//to use: <ColorMatch handler={handleSolve}>
function ColorMatch(props){
  //const [solved, setSolved] = React.useState(-1); //-1: not acted, 0: incorrect, 1: correct
  // const colors = ["error", "warning", "success", "primary", "secondary"];
  const colors = [red, orange, yellow, green, blue, purple];
  const words = ["Red", "Orange", "Yellow", "Green", "Blue", "Purple"];
  const types = ["Word", "Color"];
  let type = Math.floor(Math.random()*2);
  
  let colorA = Math.floor(Math.random()*6);
  let colorB = Math.floor(Math.random()*5);
  if(colorB >= colorA){
    colorB ++;
  }
  
  let targetWords = [words[colorA], words[colorB]];
  let targetColors = [colors[colorA], colors[colorB]];
  
  let target = Math.floor(Math.random()*2);

  return (
    <div>
      <br></br>
      <h1>Choose {types[type]} {targetWords[target]}</h1>
      <br></br>
      <Button variant="outlined" size="large" variant="contained" sx={{ backgroundColor: colors[colorA][500] }}>{words[colorB]}</Button>
      <Button variant="outlined" size="large" variant="contained" sx={{ backgroundColor: colors[colorB][500] }}>{words[colorA]}</Button>
    </div>
  );
}
export default ColorMatch;
