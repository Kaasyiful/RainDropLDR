function Details() {

    return (
        <>
            <header><div className="pricing-header p-3 pb-md-4 mx-auto text-center"><h1 className="display-4 fw-normal text-body-emphasis">Pricing</h1><p className="fs-5 text-body-secondary">Quickly build an effective pricing table for your potential customers with this Bootstrap example. It?s built with default Bootstrap components and utilities with little customization.</p></div></header>

            <div className="container my-5">
                <div className=" p-5 text-center bg-body-tertiary rounded-3">
                    <div className="col">
                        <div className="card mb-4 rounded-3 shadow-sm">
                            <div className="card-header py-3">
                                <h4 className="my-0 fw-normal"></h4>
                            </div>
                            <div className="card-body">
                                <h1 className="card-title pricing-card-title">$0<small className="text-body-secondary fw-light">/mo</small></h1>
                                <ul className="list-unstyled mt-3 mb-4">
                                    NIM:<br />
                                    Kelas:
                                </ul>
                                <button type="button" className="w-100 btn btn-lg btn-outline-primary">Sign up for free</button>
                            </div>
                        </div>
                    </div>
                    <h1 className="text-body-emphasis">Basic jumbotron</h1>
                    <p className="lead">
                        This is a simple Bootstrap jumbotron that sits within a <code>.container</code>, recreated with built-in utility  classNamees.
                    </p>
                </div>
            </div>
        </>
    )
}

export default Details