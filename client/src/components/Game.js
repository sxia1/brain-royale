import * as React from 'react';
import ReactDOM from 'react-dom';

import Container from '@mui/material/Container';
import Grid from '@mui/material/Grid';
import Box from '@mui/material/Box';

import { red, pink, purple, deepPurple, indigo, blue, lightBlue, cyan, teal, green, lightGreen, lime, yellow, amber, orange, deepOrange, brown, grey, blueGrey } from '@mui/material/colors';

import Puzzle from './Puzzle';
import Player from './Player';





function Game(props) {

    return (
        <Container sx={{ width: '100%' }}>
            <Grid container sx={{ justifyContent: 'center', alignContent: 'flex-start' }}>
                <Box sx={{ width: 1/4 }}>
                    <Box sx={{ height: 90 }} />
                    <Box sx={{ display: 'flex', flexWrap: 'wrap', justifyContent: 'space-between' }}>
                        {Array.from(new Array(45)).map((item, index) => (<Player />))}
                    </Box>
                </Box>

                <Box sx={{ display: 'flex', flexWrap: 'wrap', justifyContent: 'center', alignContent: 'center',  width: 1/2}}>
                    <Puzzle />
                </Box>

                <Box sx={{ width: 1/4 }}>
                    <Box sx={{ height: 90 }} />
                    <Box sx={{ display: 'flex', flexWrap: 'wrap', justifyContent: 'space-between' }}>
                        {Array.from(new Array(45)).map((item, index) => (<Player />))}
                    </Box>
                </Box>

            </Grid>
        </Container>
    );
}

export default Game; 
