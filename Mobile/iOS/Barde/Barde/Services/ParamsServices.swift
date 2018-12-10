//
//  ParamsServices.swift
//  Barde
//
//  Created by Arnaud Perrault on 10/12/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import Alamofire

class ParamsServices {
    func saveParams() {
        let parameters: Parameters = [
            "style": UserDefaults.standard.array(forKey: "styleArray"),
            "chords": UserDefaults.standard.array(forKey:"chordsArray"),
            "arpeggios": UserDefaults.standard.array(forKey:"arpegiosArray"),
            "battery": UserDefaults.standard.array(forKey:"battery"),
            "tempo": UserDefaults.standard.integer(forKey:"tempoValue"),
            "name":  UserDefaults.standard.string(forKey:"paramsName")

        ]
        
        print(parameters)
    }
}
