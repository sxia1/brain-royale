import * as React from 'react';
import ReactDOM from 'react-dom';

import Box from '@mui/material/Box';
import Typography from '@mui/material/Typography';
import Skeleton from '@mui/material/Skeleton';
import Tooltip from '@mui/material/Tooltip';

import LinearProgress from '@mui/material/LinearProgress';

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

import ArrowForwardIcon from '@mui/icons-material/ArrowForward';

import ColorMatch from './ColorMatch';
import ColorMatchContainer from '../containers/ColorMatchContainer';

import { red, pink, purple, deepPurple, indigo, blue, lightBlue, cyan, teal, green, lightGreen, lime, yellow, amber, orange, deepOrange, brown, grey, blueGrey } from '@mui/material/colors';


function PuzzleCounter(props) {
    const [maxPuzzles, setMaxPuzzles] = React.useState(20);

    return (
        <Box sx={{ align: 'right' }} > 
            <Typography component="span"> {props.countPuzzles} </Typography>
            <Typography component="span" sx={{ color: '#b71c1c' }}> (+ {props.countSent}) </Typography>
            <Typography component="span" > 🧩 / {maxPuzzles} </Typography>
        </Box>
    );
}

function PuzzleTimer(props) {
    let countdown = `00:${props.count < 0 ? '00' : (props.count).toString().padStart(2, "0")}`

    return (
        <Box>
            <Typography variant="h3" gutterBottom component="div" 
                sx={{ fontFamily: 'Monospace', textAlign: 'center', 
                        color: (props.count > (props.max * .5) || props.count < 0 ? '#000000' : '#b71c1c') }}>
                {countdown}
            </Typography>
        </Box>
    );
}

function AttackStyle(props) {
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

            <ToggleButton value="random" aria-label="random" sx={{ fontSize: 12 }}>
                <Tooltip title="send some rando a puzzle">
                    <span>Attack{attack === "random" ? <SportsKabaddiIcon fontSize="small" sx={{ ml: 1/2 }} /> : <SportsMmaIcon fontSize="small" sx={{ ml: 1/2 }} /> }</span>
                </Tooltip>
            </ToggleButton>
        </ToggleButtonGroup>
    </Box>
    );

}

class Puzzle extends React.Component {
    constructor(props) {
        super(props);
        console.log(props);
        this.state = { count: 10, max: 10, info: "", puzzle_stack: 10, streak: 0};
    }
        
    componentDidMount() {
        if (this.props.websocket != null){
            this.requestPuzzle();
            this.getPuzzle();
        }
        this.intervalID = setInterval(() => {
            this.state.count = this.state.count - 0.1;
        }, 100);
    }

    componentDidUpdate() {
        clearInterval(this.intervalID);

        this.state.count = 10;
        this.intervalID = setInterval(() => {
            this.state.count = this.state.count - 0.1;
        }, 100);
        //IF TIMER RAN OUT UPDATE COUNTER AND REQUEST NEW PUZZLE
    }

    componentWillUnmount() {
        clearInterval(this.intervalID);
    }

    requestPuzzle = () => {
        var request = {
            "type": "generatePuzzle",
            "lobby_id": 1
        };
        this.props.websocket.send(JSON.stringify(request));
    }

    attackPlayer = () => {
        var request = {
            "type": "attack",
            "lobby_id": 1
        };
        this.props.websocket.send(JSON.stringify(request));
    }

    getPuzzle = () => {
        this.props.websocket.onmessage = (e) => {
            var msg = JSON.parse(e.data);
            this.state.info = msg;
        }
    }

    render(){
        return (
            <Box>
                <PuzzleTimer count={count} max={max} />
                <Box container sx={{ display: 'flex', flexWrap: 'wrap', 
                        justifyContent: 'space-between', alignItems: 'center' }}>
                    <AttackStyle />
                    <PuzzleCounter />
                </Box>
                <Box color={progressBarColor} sx={{ pt: 2 }}>
                    <LinearProgress variant="determinate" sx={{ height: 5 }}
                        color='inherit'
                        value={count * (100/max) } />
                </Box>
                <Box container sx={{ width:600, justifyContent:'space-between', alignItems: 'center', p: 2, mt: 2, mb: 10 }}>
                    <ColorMatch info={info}/>
                </Box>
            </Box>
        );
    };
}

/*
            <Skeleton variant="rectangular" animation="wave" 
                sx={{ bgcolor: '#cfd8dc' }} 
                height={450} width={600} />
 */
export default Puzzle; 
