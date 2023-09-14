import { Box, Grid, Stack, Typography } from "@mui/material";
import React from "react";
import { Plan } from "../types/Plan";
import CardPlanSection from "./CardPlanSection";

export const plans: Plan[] = [
  {
    title: "Website",
    description: "Crea un catálogo profesional y atractivo que sorprenda.",
    price: 2990,
    hrefViewMore: "#",
    hrefSelectPlan: "/comprar/0",
  },
  {
    title: "Business",
    description:
      "Comienza a vender al instante con los elementos esenciales del eCommerce.",
    price: 5990,
    hrefViewMore: "#",
    hrefSelectPlan: "/comprar/1",
  },
  {
    title: "Advanced Store",
    description:
      "Haz crecer tu negocio con potentes herramientas de marketing.",
    price: 8990,
    hrefViewMore: "#",
    hrefSelectPlan: "/comprar/2",
  },
];

const PlansSection = () => {
  return (
    <Stack spacing={2}>
      <Typography textAlign={"center"} variant="h4" className="title">
        Elije el plan que mejor te convenga
      </Typography>
      <Box>
        <Grid container spacing={4}>
          {plans.map((item, index) => (
            <Grid item key={index} xs={12} md={4}>
              <CardPlanSection item={item} />
            </Grid>
          ))}
        </Grid>
      </Box>
    </Stack>
  );
};

export default PlansSection;
