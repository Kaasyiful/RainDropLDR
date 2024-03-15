import '../assets/pricing.css'
import Data from '../assets/biodata.json'

let data = JSON.stringify(Data["Mahasiswa"])
let ardata:Array<Object> = JSON.parse(data)
let contoh = 0

export function InAbout({contoh}) {
    let datain = JSON.stringify(ardata.at(contoh))
    let ardatain: Array<string> = JSON.parse(datain)
    let datanama = JSON.stringify(ardatain.nama)
    let nama = datanama.slice(1, -1)
    let datanim = JSON.stringify(ardatain.nim)
    let nim = datanim.slice(1, -1)
    let datakelas = JSON.stringify(ardatain.kelas)
    let kelas = datakelas.slice(1, -1)

    return (
        <div className="col">
            <div className="card mb-4 rounded-3 shadow-sm">
                <div className="card-header py-3">
                    <h4 className="my-0 fw-normal">{nama}</h4>
                </div>
                <div className="card-body">
                    <h1 className="card-title pricing-card-title">$0<small className="text-body-secondary fw-light">/mo</small></h1>
                    <ul className="list-unstyled mt-3 mb-4">
                        NIM: {nim} <br />
                        Kelas: {kelas}
                    </ul>
                    <button type="button" className="w-100 btn btn-lg btn-outline-primary">Sign up for free</button>
                </div>
            </div>
        </div>
    )
}

function About() {
    return (
        <>
            <div className="container py-3">
                <header>
                    <div className="pricing-header p-3 pb-md-4 mx-auto text-center">
                        <h1 className="display-4 fw-normal text-body-emphasis">Pricing</h1>
                        <p className="fs-5 text-body-secondary">Quickly build an effective pricing table for your potential customers with this Bootstrap example. It’s built with default Bootstrap components and utilities with little customization.</p>
                    </div>
                </header>

                <main>
                    <div className="row row-cols-1 row-cols-md-4 mb-3 text-center">
                        <InAbout contoh={0} />
                        <InAbout contoh={1} />
                        <InAbout contoh={2} />
                        <InAbout contoh={3} />
                    </div>
                </main>
            </div>
        </>
    )
}

export default About