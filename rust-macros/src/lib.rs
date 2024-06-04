extern crate proc_macro;

use proc_macro::TokenStream;
use quote::quote;
use syn::{Data, DeriveInput, Fields, FieldsNamed};

fn get_fields(data: &Data) -> FieldsNamed {
    if let Data::Struct(strct) = data {
        if let Fields::Named(fields) = &strct.fields {
            fields.to_owned()
        } else {
            panic!("Can only handle named fields")
        }
    } else {
        panic!("Can only handle structs");
    }
}

fn impl_bean(ast: DeriveInput) -> TokenStream {
    let ident = ast.ident;
    let fields = get_fields(&ast.data);
    let setters = fields.named.iter().map(|field| {
        let name = field.ident.as_ref().unwrap();
        let ty = &field.ty;
        let f_name: proc_macro2::TokenStream = format!("set_{}", name).parse().unwrap();
        let function_signature = quote!(pub fn #f_name (&mut self, input: #ty));
        quote!(
            #function_signature {
                self.#name = input;
            }
        )
    });

    let getters = fields.named.iter().map(|field| {
        let name = field.ident.as_ref().unwrap();
        let ty = &field.ty;
        let function_signature = quote!(pub fn #name (&self) -> &#ty);
        quote!(
            #function_signature {
                &self.#name
            }
        )
    });

    quote! {
        impl #ident {
            #(#setters)*
            #(#getters)*
        }
    }
    .into()
}

#[proc_macro_derive(Bean)]
pub fn my_macro_here_derive(input: TokenStream) -> TokenStream {
    let ast: DeriveInput = syn::parse(input).unwrap();

    impl_bean(ast)
}
