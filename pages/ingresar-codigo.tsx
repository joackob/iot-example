import { Box, Button, Modal, Skeleton, Stack, Typography } from "@mui/material";
import { useState } from "react";

const IngresarCodigo = () => {
  const [open, setOpen] = useState(false);
  const handleOpen = () => setOpen(true);
  const handleClose = () => setOpen(false);
  return (
    <Stack alignItems="center" spacing={2}>
      <Skeleton variant="rectangular" width={480} height={480} />
      <Button variant="contained" onClick={handleOpen}>
        Ingresar Codigo Manualmente
      </Button>
      <Modal open={open} onClose={handleClose}>
        <Stack alignItems="center" justifyContent={"center"} height={"100%"}>
          <Box
            sx={{ backgroundColor: "white", width: "480px", height: "480px", paddingTop:"50px"}}
          >
            <Typography variant="h5" textAlign={"center"}>Clave de desbloqueo</Typography>
            <Typography variant="h6" textAlign={"center"}>
              Ingrese la secuencia de letras que aparecen debajo del codigo QR
            </Typography>
          </Box>
        </Stack>
      </Modal>
    </Stack>
  );
};

export default IngresarCodigo;
