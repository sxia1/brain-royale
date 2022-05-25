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
const answers = ["left", "right"];

class ColorMatchContainer extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            correct: null,
            puzzle_type: "word",
            left_word: "red",
            left_color: colors[0],
            right_word: "blue",
            right_color: colors[4],
            correct_word: "red"
        };
    }

    componentDidMount() {
        let type = types[Math.floor(Math.random() * types.length)];
        let correct_rand = Math.floor(Math.random() * types.length);

        let correct = answers[correct_rand % 2];
        let correct_color = colors[correct_rand];
        let correct_word = words[correct_rand];
        let left_color, right_color, left_word, right_word;

        let incorrect_color = colors[Math.floor(Math.random()* colors.length)];
        let incorrect_word = words[Math.floor(Math.random() * words.length)];

        //note that 'incorrect' is a general misnomer as some matches can occur
        //we only want to ensure that if we ask to choose the correct word or color
        //that there is only one instance of the word or color in each respective case
        while (type == "word" && incorrect_word == correct_word) {
            incorrect_word = words[Math.floor(Math.random() * words.length)];
        }

        while (type == "color" && incorrect_color == correct_color) {
            incorrect_color = colors[Math.floor(Math.random()* colors.length)];
        }


        if (type == "word") {
            if (correct == "left") {
                left_word = correct_word;
                right_color = correct_color;
                right_word = incorrect_word;
                left_color = incorrect_color;
            }
            else {
                right_word = correct_word;
                left_color = correct_color;
                left_word = incorrect_word;
                right_color = incorrect_color;
            }
        }

        else {
            if (correct == "left") {
                left_color = correct_color;
                right_word = correct_word;
                right_color = incorrect_color;
                left_word  = incorrect_word;
            }

            else {
                right_color = correct_color;
                left_word = correct_word;
                left_color = incorrect_color;
                right_word = incorrect_word;
            }
        }

        this.setState({
            correct: correct,
            puzzle_type: type,
            left_word: left_word,
            left_color: left_color,
            right_word: right_word,
            right_color: right_color,
            correct_word: correct_word
        }); 
    }

    render() {
        return (
            <ColorMatch info={this.state} onChange={this.props.onChange} />
        );
    }   
}

export default ColorMatchContainer;