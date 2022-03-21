import * as React from 'react';
import ReactDOM from 'react-dom';

import Box from '@mui/material/Box';
import Typography from '@mui/material/Typography';
import Skeleton from '@mui/material/Skeleton';
import LinearProgress from '@mui/material/LinearProgress';
import Tooltip from '@mui/material/Tooltip';


import Button from '@mui/material/Button';
import ButtonGroup from '@mui/material/ButtonGroup';
import ToggleButton from '@mui/material/ToggleButton';
import ToggleButtonGroup from '@mui/material/ToggleButtonGroup';

import KeyboardDoubleArrowDownIcon from '@mui/icons-material/KeyboardDoubleArrowDown';
import KeyboardArrowDownIcon from '@mui/icons-material/KeyboardArrowDown';

import SportsMmaIcon from '@mui/icons-material/SportsMma';
import SportsKabaddiIcon from '@mui/icons-material/SportsKabaddi';

import ShuffleIcon from '@mui/icons-material/Shuffle';
import ShuffleOnIcon from '@mui/icons-material/ShuffleOn';



import { red, pink, purple, deepPurple, indigo, blue, lightBlue, cyan, teal, green, lightGreen, lime, yellow, amber, orange, deepOrange, brown, grey, blueGrey } from '@mui/material/colors';


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

function AttackStyle(props) {
    // https://mui.com/components/button-group/#split-button could also be nice 
    return (
        <ButtonGroup size="small" variant="contained" aria-label="outlined primary button group">
            <Button>Loss</Button>
            <Button>Retaliation</Button>
            <Button>Random</Button>
        </ButtonGroup>
    );

}

function AttackStyle2(props) {
    const [attack, setAttack] = React.useState('loss');
    
    function handleChange(event, value) {
        setAttack(value);
    }

    return (
        <Box>
        <ToggleButtonGroup size="small" exclusive aria-label="attack style"
            orientation={props.orientation || 'horizontal'}
            color="error" value={attack}
            sx={{ height: 30, width: 'auto', fontSize: 8 }}
            onChange={handleChange} >

            <ToggleButton value="loss" aria-label="loss" sx={{ fontSize: 12 }}>
                <Tooltip title="send a puzzle to the worst performing player and destroy their dreams of being big brain">
                    <span>Loss {attack == "loss" ? <KeyboardDoubleArrowDownIcon fontSize="small" sx={{ ml: 1/2 }} /> : <KeyboardArrowDownIcon fontSize="small" sx={{ ml: 1/2 }} /> }</span>
                </Tooltip>
            </ToggleButton>

            <ToggleButton value="retaliation" aria-label="retaliation" sx={{ fontSize: 12 }}>
                <Tooltip title="retaliate against a person who sent you a puzzle">
                    <span>Retaliation {attack == "retaliation" ? <SportsKabaddiIcon fontSize="small" sx={{ ml: 1/2 }} /> : <SportsMmaIcon fontSize="small" sx={{ ml: 1/2 }} /> }</span>
                </Tooltip>
            </ToggleButton>

            <ToggleButton value="random" aria-label="random" sx={{ fontSize: 12 }}>
                <Tooltip title="send some rando a puzzle">
                    <span>Random {attack == "random" ? <ShuffleOnIcon fontSize="small" sx={{ ml: 1/2 }} /> : <ShuffleIcon fontSize="small" sx={{ ml: 1/2 }} /> }</span>
                </Tooltip>
            </ToggleButton>
        </ToggleButtonGroup>
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
    if (count > 14) {
        progressBarColor = red[900];
    }
    else if (count > 10) {
        progressBarColor = red[500];
    }
    else if (count > 6) {
        progressBarColor = deepPurple[500];
    }

    // let attack = <AttackStyle />; 
    let attack = <AttackStyle2 />; 

    return (
        <Box>
            <PuzzleTimer count={count} />
            <Box container sx={{ display: 'flex', flexWrap: 'wrap', 
                    justifyContent: 'space-between', alignItems: 'center' }}>

                {attack}
                <PuzzleCounter />
            </Box>
            <Box color={progressBarColor} sx={{ pt: 2 }}>
                <LinearProgress variant="determinate" sx={{ height: 5 }}
                    color='inherit'
                    value={count * 5} />
            </Box>
            <Skeleton variant="rectangular" animation="wave" 
                sx={{ bgcolor: '#cfd8dc' }} 
                height={450} width={600} />
        </Box>
    );
}

export default Puzzle; 
