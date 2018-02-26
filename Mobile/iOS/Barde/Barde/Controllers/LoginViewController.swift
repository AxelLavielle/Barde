//
//  LoginViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 19/12/2017.
//  Copyright © 2017 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit
import Alamofire
import SwiftyJSON

class LoginViewController: UIViewController {
    
    @IBOutlet weak var emailTextField: UITextField!
    @IBOutlet weak var passwordTextField: UITextField!
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
    }
    
    override func viewDidLoad() {
        
        setTextFieldPaddingProperty()
    }
    
    func setTextFieldPaddingProperty()
    {
        let emailPaddingView: UIView = UIView.init(frame: CGRect(x: 0, y: 0, width: 5, height: 20))
        emailTextField.leftView = emailPaddingView
        emailTextField.leftViewMode = .always
        let passwordPaddingView: UIView = UIView.init(frame: CGRect(x: 0, y: 0, width: 5, height: 20))
        passwordTextField.leftView = passwordPaddingView
        passwordTextField.leftViewMode = .always
    }
    
    @IBAction func buttonClose(_ sender: Any) {
        self.dismiss(animated: true, completion: nil)
    }
    
    @IBAction func buttonLogin(_ sender: Any) {
        
        let parameters: Parameters = [
            "email":  emailTextField.text ?? "",
            "password": passwordTextField.text ?? "",
            ]
        
        Alamofire.request(Utils().getApiUrl() + "/auth/login", method:.post, parameters: parameters).responseJSON { response in
            print("Request: \(String(describing: response.request))")   // original url request
            print("Response: \(String(describing: response.response))") // http url response
            print("Result: \(String(describing: response.result.value))")
            // response serialization result
            
            if let httpStatusCode = response.response?.statusCode {
                switch(httpStatusCode) {
                case 200:
                    
                    if ((response.result.value) != nil) {
                        let data = JSON(response.result.value!)
                        
                        UserDefaults.standard.set(data["data"]["token"].stringValue, forKey: "Token")
                        UserDefaults.standard.set(self.emailTextField.text, forKey: "Email")
                        self.performSegue(withIdentifier: "ToMainView", sender: self)
                    }
                    break
                case 400:
                    let refreshAlert = UIAlertController(title: "Wrong content", message: "The email or password is incorrect.", preferredStyle: UIAlertControllerStyle.alert)
                    
                    refreshAlert.addAction(UIAlertAction(title: "Ok", style: .default, handler: { (action: UIAlertAction!) in
                    }))
                    
                    self.present(refreshAlert, animated: true, completion: nil)
                    break
                default:
                    print("default")
                    
                }
            }
        }
    }
    
    func test() {
        
        let profil = Profil(context: context)
        profil.email = "test@outlook.fr"
        profil.firstname = "Test1"
        profil.lastname = "Test2"
        
        ad.saveContext()
    }
    
    
    
}
