import { AppRegistration, Login, Lock, LockOpen } from "@mui/icons-material";
import { Box } from "@mui/material";
import React from "react";
import NavDesktop from "./NavDesktop";
import NavMobile from "./NavMobile";

const linksLeft = [
  {
    label: "Beneficios",
    href: "/",
    icon: <Lock />,
  },
  {
    label: "Campaña",
    href: "/",
    icon: <LockOpen />,
  },
];

const linksRight = [
  {
    label: "Iniciar sesión",
    href: "/",
    icon: <Login />,
  },
  {
    label: "Registrarse",
    href: "/",
    icon: <AppRegistration />,
  },
];

const Header = () => (
  <Box component={"header"}>
    <Box>
      <Box
        display={{
          xs: "none",
          md: "block",
        }}
      >
        <NavDesktop linksLeft={linksLeft} linksRight={linksRight} />
      </Box>

      <Box
        display={{
          xs: "block",
          md: "none",
        }}
      >
        <NavMobile linksLeft={linksLeft} linksRight={linksRight} />
      </Box>
    </Box>
  </Box>
);

export default Header;
