function Footer() {

    return (
        <>
            <div className="b-example-divider"></div>
            <div className="container">
                <footer className="py-3 my-4">
                    <ul className="nav justify-content-center border-bottom pb-3 mb-3">
                        <li className="nav-item"><a href="/" className="nav-link px-2 text-body-secondary">Beranda</a></li>
                        <li className="nav-item"><a href="/details" className="nav-link px-2 text-body-secondary">Rincian</a></li>
                        <li className="nav-item"><a href="/about" className="nav-link px-2 text-body-secondary">Tentang</a></li>
                    </ul>
                    <p className="text-center text-body-secondary">© 2024 Company, Inc</p>
                </footer>
            </div>
        </>
    )
}

export default Footer