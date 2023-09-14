import {
  Box,
  Button,
  Card,
  CardActions,
  CardContent,
  CardHeader,
  Container,
  Typography,
} from "@mui/material";

const Compras = ({
  title,
  description,
  price,
}: {
  title: string;
  description: string;
  price: number;
}) => {
  return (
    <Container
      style={{
        marginTop: "4rem",
      }}
    >
      <Typography
        style={{
          marginBottom: "2rem",
        }}
        variant="h4"
        align="center"
      >
        Solo falta un paso más...
      </Typography>
      <Card
        sx={{
          minHeight: "345px",
          display: "flex",
          flexDirection: "column",
          justifyContent: "space-between",
          p: 2,
        }}
        elevation={4}
      >
        <CardHeader title={title} subheader={description} />
        <Box>
          <CardContent>
            <Typography variant="caption">Desde</Typography>
            <Typography variant="h4" className="title">
              {`AR$ ${price
                .toString()
                .replace(/\B(?=(\d{3})+(?!\d))/g, ".")},00`}
            </Typography>
            <Typography variant="caption">/mes</Typography>
          </CardContent>
          <CardActions>
            <Button variant="contained" className="button contained" href="#">
              Comprar
            </Button>
          </CardActions>
        </Box>
      </Card>
    </Container>
  );
};

export default Compras;
