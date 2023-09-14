import {
  Box,
  Button,
  Card,
  CardActions,
  CardContent,
  CardHeader,
  Stack,
  Typography,
} from "@mui/material";
import React from "react";
import { Plan } from "../types/Plan";

const CardPlanSection = ({ item }: { item: Plan }) => {
  return (
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
      <CardHeader title={item.title} subheader={item.description} />
      <Box>
        <CardContent>
          <Typography variant="caption">Desde</Typography>
          <Typography variant="h4" className="title">
            {`AR$ ${item.price
              .toString()
              .replace(/\B(?=(\d{3})+(?!\d))/g, ".")},00`}
          </Typography>
          <Typography variant="caption">/mes</Typography>
        </CardContent>
        <CardActions>
          <Button
            variant="contained"
            className="button contained"
            href={item.hrefSelectPlan}
          >
            Seleccionar
          </Button>
          <Button
            variant="text"
            className="button button-text"
            href={item.hrefViewMore}
          >
            Ver más
          </Button>
        </CardActions>
      </Box>
    </Card>
  );
};

export default CardPlanSection;
