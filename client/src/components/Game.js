import * as React from 'react';
import ReactDOM from 'react-dom';

import Container from '@mui/material/Container';
import Grid from '@mui/material/Grid';
import Box from '@mui/material/Box';

import { red, pink, purple, deepPurple, indigo, blue, lightBlue, cyan, teal, green, lightGreen, lime, yellow, amber, orange, deepOrange, brown, grey, blueGrey } from '@mui/material/colors';

import Puzzle from './Puzzle';
import Player from './Player';





class Game extends React.Component {
    render() {
        // 99 - 1 = 98 / 2 = 49 
        let numPlayers = (31 - 1)/2;


        return (
            <Grid container sx={{ justifyContent: 'space-around', alignContent: 'flex-start', 
                width: '100%' }}>

                <Box sx={{ width: 1/5 }}>
                    <Box sx={{ height: 90 }} />

                    <Box sx={{ display: 'flex', flexWrap: 'wrap', justifyContent: 'space-evenly' }}>
                        {Array.from(new Array(numPlayers)).map((item, index) => (<Player />))}
                    </Box>
                </Box>

                <Box sx={{ display: 'flex', flexWrap: 'wrap', justifyContent: 'center', alignContent: 'center' }}>
                    <Puzzle />
                </Box>

                <Box sx={{ width: 1/5 }}>
                    <Box sx={{ height: 90 }} />

                    <Box sx={{ display: 'flex', flexWrap: 'wrap', justifyContent: 'space-evenly' }}>
                        {Array.from(new Array(numPlayers)).map((item, index) => (<Player />))}
                    </Box>
                </Box>

            </Grid>
        );
    };
}

export default Game; 
