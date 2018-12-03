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
    
    @IBOutlet weak var scrollView: UIScrollView!
    @IBOutlet weak var emailTextField: UITextField!
    @IBOutlet weak var passwordTextField: UITextField!
    @IBOutlet weak var passwordImageView: UIImageView!
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
    }
    
    override func viewDidLoad() {
        
        let notificationCenter = NotificationCenter.default
        notificationCenter.addObserver(self, selector: #selector(adjustForKeyboard), name: UIResponder.keyboardWillHideNotification, object: nil)
        notificationCenter.addObserver(self, selector: #selector(adjustForKeyboard), name: UIResponder.keyboardWillChangeFrameNotification, object: nil)
        
        let tap: UITapGestureRecognizer = UITapGestureRecognizer(target: self, action: #selector(dismissKeyboard))
        tap.cancelsTouchesInView = false
        view.addGestureRecognizer(tap)
        
        configureView()
    }

    
    @objc func dismissKeyboard(){
        view.endEditing(true)
    }
    
    func configureView()
    {
        let emailPaddingView: UIView = UIView.init(frame: CGRect(x: 0, y: 0, width: 5, height: 20))
        emailTextField.leftView = emailPaddingView
        emailTextField.leftViewMode = .always

        let passwordPaddingView: UIView = UIView.init(frame: CGRect(x: 0, y: 0, width: 5, height: 20))
        passwordTextField.leftView = passwordPaddingView
        passwordTextField.leftViewMode = .always
        
        let passwordTapGestureRecognizer = UITapGestureRecognizer(target: self, action: #selector(passwordIvAction(tapGestureRecognizer:)))
        passwordImageView.isUserInteractionEnabled = true
        passwordImageView.addGestureRecognizer(passwordTapGestureRecognizer)
    }
    
    @IBAction func myTextFieldTouchDown(_ sender: UITextField) {
        TextFieldManager.sharedInstance.highlightSelected(textfield: sender)
    }
   
    @IBAction func myTextFieldEditingDidEnd(sender: UITextField) {
       
        if(sender.text?.trimmingCharacters(in: .whitespacesAndNewlines) == ""){
            TextFieldManager.sharedInstance.errorHighlight(textField: sender)
        }
        else {
            TextFieldManager.sharedInstance.removeErrorHighlight(textField: sender)
        }
    }

    @objc func adjustForKeyboard(notification: Notification) {
        let userInfo = notification.userInfo!
        
        let keyboardScreenEndFrame = (userInfo[UIResponder.keyboardFrameEndUserInfoKey] as! NSValue).cgRectValue
        let keyboardViewEndFrame = view.convert(keyboardScreenEndFrame, from: view.window)
        
        if notification.name == UIResponder.keyboardWillHideNotification {
            scrollView.contentInset = UIEdgeInsets.zero
        } else {
            scrollView.contentInset = UIEdgeInsets(top: 0, left: 0, bottom: keyboardViewEndFrame.height, right: 0)
        }
    }
    
    @IBAction func buttonClose(_ sender: Any) {
        self.dismiss(animated: true, completion: nil)
    }
    
    @objc func passwordIvAction(tapGestureRecognizer: UITapGestureRecognizer)
    {
        _ = tapGestureRecognizer.view as! UIImageView
        
        passwordTextField.isSecureTextEntry = !passwordTextField.isSecureTextEntry
    }
    
    @IBAction func buttonLogin(_ sender: Any) {
        
        if (emailTextField.text!.isEmpty || passwordTextField.text!.isEmpty) {
            Alert.showRequiredField(on: self)
            self.myTextFieldEditingDidEnd(sender: self.emailTextField)
            self.myTextFieldEditingDidEnd(sender: self.passwordTextField)
            
        } else {
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
                    let data = JSON(response.result.value!)
                    switch(httpStatusCode) {
                    case 200:
                        
                        if ((response.result.value) != nil) {
                            UserDefaults.standard.set(data["data"]["token"].stringValue, forKey: "Token")
                            UserDefaults.standard.set(self.emailTextField.text, forKey: "Email")
                                self.openTutorial()
                        }
                        break
                    case 400:
                        let refreshAlert = UIAlertController(title: NSLocalizedString("WrongContent.text", comment: ""), message: NSLocalizedString("WrongContentDescription.text", comment: ""), preferredStyle: UIAlertController.Style.alert)
                        
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
        
    }
    
    func openTutorial() {
        let storyBoard: UIStoryboard = UIStoryboard(name: "Main", bundle: nil)
        
        if (!UserDefaults.standard.bool(forKey: "tutorial")) {
            UserDefaults.standard.set(true, forKey: "fromLogin")
            self.performSegue(withIdentifier: "Tutorial", sender: self)
        } else {
            self.performSegue(withIdentifier: "ToMainView", sender: self)
        }
    }
}
