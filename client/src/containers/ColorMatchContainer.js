import * as React from 'react';
import { useState, useEffect } from 'react';
import ReactDOM from 'react-dom';

import Box from '@mui/material/Box';
import Typography from '@mui/material/Typography';
import Button from '@mui/material/Button';

import { red, pink, purple, deepPurple, indigo, blue, lightBlue, cyan, teal, green, lightGreen, lime, yellow, amber, orange, deepOrange, brown, grey, blueGrey } from '@mui/material/colors';
import ColorMatch from '../components/ColorMatch';

//needs left color, right color, left word, right word, correct choice, puzzle type, update function

const colors = [red[500], orange[500], yellow[600], green[500], blue[500], purple[500]];
const words = ["Red", "Orange", "Yellow", "Green", "Blue", "Purple"];
const types = ["word", "color"];

class ColorMatchContainer extends React.Component {
    constructor(props) {
        super(props);

    }

    handleClick(correct) {
        if (correct) {
            this.props.
        }
    }

    return (
        <ColorMatch leftColor/>
    );
}

export default ColorMatchContainer;