import Container from '@mui/material/Container';
import Box from '@mui/material/Box';
import Typography from '@mui/material/Typography';

export default function ErrorPage (props) {
	return (
        <Box sx={{ m: 2 }}>
            <Typography variant="h3" sx={{ textAlign: 'center', fontFamily: 'monospace', mb: 4 }}>
                Error :(
            </Typography>
            <Typography variant="h5" sx={{ textAlign: 'center', fontFamily: 'monospace' }}>
                { props.message }
            </Typography>
        </Box>
	);
}

