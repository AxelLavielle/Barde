//
//  AlertServices.swift
//  Barde
//
//  Created by Arnaud Perrault on 28/07/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

struct Alert {
    
    static func showBasic (on vc:UIViewController, with title: String, message: String) {
        let alert = UIAlertController(title: title, message: message, preferredStyle: UIAlertControllerStyle.alert)
        alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
        DispatchQueue.main.async { vc.present(alert, animated: true, completion: nil) }
    }
    
    static func showIncompleteForm(on vc:UIViewController) {
        showBasic(on: vc, with: "Incomplete form", message: "Please fill out all fields in the form")
    }
    
    static func showUnableToRetrieveData(on vc: UIViewController) {
        showBasic(on: vc, with: "Unable to retrieve data", message: "Network error")
    }
    
    static func showUnableToConnectToGeneratorServer(on vc:UIViewController) {
        showBasic(on: vc, with: "Unable to connect to generator server", message: "Network error")
    }
    
    static func showUnableToConnectToDataServer(on vc:UIViewController) {
        showBasic(on: vc, with: "Unable to connect to data server", message: "Network error")
    }
}
