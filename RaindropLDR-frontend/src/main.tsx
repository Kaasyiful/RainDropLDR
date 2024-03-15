import * as React from "react";
import * as ReactDOM from "react-dom/client";
import App, {Footer} from "./App";

ReactDOM.createRoot(document.getElementById("root")!).render(
  <React.StrictMode>
        <App />
        <Footer />
  </React.StrictMode>
);
