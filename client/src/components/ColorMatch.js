import * as React from 'react';
import { useState } from 'react';
import ReactDOM from 'react-dom';

import Box from '@mui/material/Box';
import Typography from '@mui/material/Typography';
import Button from '@mui/material/Button';

import { red, pink, purple, deepPurple, indigo, blue, lightBlue, cyan, teal, green, lightGreen, lime, yellow, amber, orange, deepOrange, brown, grey, blueGrey } from '@mui/material/colors';

//to use: <ColorMatch handler={handleSolve}>
class ColorMatch extends React.Component{
    constructor(props) {
        super(props);
    }

    render() {
        //console.log("I'm here and this is props:", this.props);
        return (
            <div>
                <Typography variant="h6" sx={{ mb: 2 }}>Choose the { this.props.info.puzzle_type }: { this.props.info.correct_word }</Typography>

                <Box sx={{ display: 'flex', flexWrap: 'wrap', justifyContent: 'space-evenly' }}>
                    <Box onClick={this.props.onChange("left")}
                    sx={{ backgroundColor: this.props.info.left_color, color: '#ffffff',  width: 1/3, m: 1, p: 3, textAlign: 'center' }}>
                        <Typography variant="h5">{this.props.info.left_word}</Typography>
                    </Box>

                    <Box onClick={this.props.onChange("right")}
                    sx={{ backgroundColor: this.props.info.right_color, color: '#ffffff', width: 1/3, m: 1, p: 3, textAlign: 'center' }}>
                        <Typography variant="h5">{this.props.info.right_word}</Typography>
                    </Box>
                </Box>
            </div>
        );
    }
};

export default ColorMatch;
