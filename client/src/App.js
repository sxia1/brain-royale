//import logo from './logo.svg';
//import './App.css';

import Landing from './components/Landing';
import Game from './components/Game';
import Container from '@mui/material/Container';
import Box from '@mui/material/Box';

/*

      <Landing />
      <Box sx={{ height: 50}}/>

*/

function App() {
  return (
    <Container maxWidth={false} sx={{ mt: 2, mb: 10, mx: 0 }}>
      <Game />
    </Container>
  );
}

export default App;
