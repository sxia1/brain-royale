import * as React from 'react';
import ReactDOM from 'react-dom';

import { typography, flexbox, grid, sizing } from '@mui/system';
import Container from '@mui/material/Container';
import Grid from '@mui/material/Grid';
import Box from '@mui/material/Box';
import Skeleton from '@mui/material/Skeleton';
import Typography from '@mui/material/Typography';
import LinearProgress from '@mui/material/LinearProgress';
import Button from '@mui/material/Button';

import { red, pink, purple, deepPurple, indigo, blue, lightBlue, cyan, teal, green, lightGreen, lime, yellow, amber, orange, deepOrange, brown, grey, blueGrey } from '@mui/material/colors';

import parse from 'html-react-parser';
import twemoji from 'twemoji';
// var emoji = require('emoji.json/emoji.json')
var emoji = require('emoji.json/emoji-compact.json')

const random = (items) => items[Math.floor(Math.random() * items.length)];

const material_colors = [red, pink, purple, deepPurple, indigo, blue, lightBlue, cyan, teal, green, lightGreen, lime, yellow, amber, orange, deepOrange, brown, grey, blueGrey];

function Player(props) {
    let player_color = random(material_colors);
    let player_shade = random([50, 100, 200]); // , 400]);

    function getEmoji() {
        let twimg = twemoji.parse(random(emoji));
        twimg = parse(twimg);
        twimg = Array.isArray(twimg) ? twimg[0] : twimg;
        return (twimg.props && twimg.props.src) ? twimg.props.src : getEmoji() ;
    }

    let twimg; 
    twimg = getEmoji(); 

    return (
        <Box sx={{ backgroundColor: player_color[player_shade], width: 50, height: 50, p: 1.5, m: 1/3, borderRadius: 28 }} >
            <img src={twimg} />
        </Box>
    );
}

function PuzzleCounter(props) {
    return (
        <Box sx={{ align: 'right' }} > 
            <Typography component="span"> N </Typography>
            <Typography component="span" sx={{ color: '#b71c1c' }}> (+ M) </Typography>
            <Typography component="span" > 🧩 / 20 </Typography>
        </Box>
    );
}

function PuzzleTimer(props) {
    let countdown = `00:${props.count < 0 ? '00' : (20-props.count).toString().padStart(2, "0")}`

    return (
        <Box>
            <Typography variant="h3" gutterBottom component="div" 
                sx={{ fontFamily: 'Monospace', textAlign: 'center', 
                        color: (20 - props.count > 9 || props.count < 0 ? '#000000' : '#b71c1c') }}>
                {countdown}
            </Typography>
        </Box>
    );
}

function Puzzle(props) {
    const [count, setCount] = React.useState(0);

    React.useEffect(() => {
        const timer = setInterval(() => {
            setCount((prevCount) => (prevCount >= 20 ? -1 : prevCount + 1));
        }, 1000);
        return () => {
            clearInterval(timer);
        };
    }, []);

    let progressBarColor = blue[700]; 

    console.log(count);
    if (count > 14) {
        progressBarColor = red[900];
    }
    else if (count > 10) {
        progressBarColor = red[500];
    }
    else if (count > 6) {
        progressBarColor = deepPurple[500];
    }

    return (
        <Box>
            <PuzzleTimer count={count} />
            <Box color={progressBarColor} sx={{ pt: 2 }}>
                <LinearProgress variant="determinate" sx={{ height: 5 }}
                    color='inherit'
                    value={count * 5} />

            </Box>
            <Skeleton variant="rectangular" animation="wave" 
                sx={{ bgcolor: '#cfd8dc' }} 
                height={300} width={450} />
        </Box>
    );
}

function Game(props) {

    console.log();

    return (
        <Container sx={{ width: '100%' }}>
            <Grid container sx={{ justifyContent: 'center', alignContent: 'center' }}>
                <Box sx={{ width: 1/4 }}>
                    <Box sx={{ height: 90 }} />
                    <Box sx={{ display: 'flex', flexWrap: 'wrap', justifyContent: 'space-between' }}>
                        {Array.from(new Array(40)).map((item, index) => (<Player />))}
                    </Box>
                </Box>

                <Box sx={{ display: 'flex', flexWrap: 'wrap', justifyContent: 'center', alignContent: 'center', width: 1/2}}>
                    <Puzzle />
                </Box>

                <Box sx={{ width: 1/4 }}>
                    <Box sx={{ height: 90 }} />
                    <Box sx={{ display: 'flex', flexWrap: 'wrap', justifyContent: 'space-between' }}>
                        {Array.from(new Array(40)).map((item, index) => (<Player />))}
                    </Box>
                </Box>

            </Grid>
        </Container>
    );
}

export default Game; 
