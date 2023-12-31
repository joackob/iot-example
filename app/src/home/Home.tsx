import {
  Box,
  Container,
  FormControlLabel,
  Switch,
  Typography,
} from "@mui/material";
import { ChangeEvent } from "react";

const Home = () => {
  const api = "http://192.168.0.29:3000/api/locker";
  const handleSwitch = async (
    _: ChangeEvent<HTMLInputElement>,
    checked: boolean,
  ) => {
    try {
      const controller = checked ? "open" : "close";
      await fetch(`${api}/${controller}`);
    } catch (error) {
      console.log(error);
    }
  };

  return (
    <>
      <Container maxWidth={false}>
        <Container
          sx={{
            background: "none",
          }}
        >
          <Box
            display={"grid"}
            gridTemplateColumns={{
              xs: "1fr",
              sm: "1fr 1fr",
            }}
            gridTemplateRows="auto"
            gridTemplateAreas={{
              xs: "'.' '.' 'title' 'subtitle' 'btn'",
              sm: "'. img' 'title img' 'subtitle img' 'btn img' '. img'",
            }}
            columnGap={{
              xs: 0,
              sm: 2,
            }}
            height={{
              xs: "92vh",
            }}
          >
            <Box
              gridArea={"title"}
              alignSelf={{
                xs: "end",
                sm: "end",
              }}
              textAlign={{
                xs: "center",
                sm: "left",
              }}
            >
              <Typography variant={"h3"} fontWeight="bold">
                Nuevos casilleros electronicos.
              </Typography>
            </Box>
            <Box
              textAlign={{
                xs: "center",
                sm: "left",
              }}
              gridArea={"subtitle"}
              alignSelf={{
                xs: "center",
              }}
            >
              <Typography variant="h4">
                La misma seguridad, la misma confianza.
              </Typography>
            </Box>
            <Box
              gridArea={"btn"}
              alignSelf={{
                xs: "start",
                sm: "start",
              }}
              display={"flex"}
              justifySelf={{
                xs: "center",
                sm: "left",
              }}
            >
              <FormControlLabel
                control={<Switch onChange={handleSwitch} size="medium" />}
                label="Probalo"
              />
            </Box>

            <Box
              gridArea={"img"}
              sx={{
                backgroundImage: `url("https://picsum.photos/1200/800")`,
                backgroundSize: "cover",
                backgroundPosition: "center",
                backgroundRepeat: "no-repeat",
              }}
            />
          </Box>
        </Container>
      </Container>
    </>
  );
};

export default Home;
